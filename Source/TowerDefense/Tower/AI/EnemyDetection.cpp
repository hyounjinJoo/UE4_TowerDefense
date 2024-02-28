#include "EnemyDetection.h"

#include <BehaviorTree/BlackboardComponent.h>
#include "TowerAIController.h"
#include "../../Monster/Monster.h"
#include "../MyTower.h"

UEnemyDetection::UEnemyDetection()
{
	Interval = 0.1;

	RandomDeviation = 0.f;

	NodeName = TEXT("Detect Enemy");

	m_pTarget = nullptr;
}

void UEnemyDetection::ResetTarget(AAIController* _Controller, float _DefaultDist)
{
	m_pTarget = nullptr;
	_Controller->GetBlackboardComponent()->ClearValue(TEXT("Target"));
	_Controller->GetBlackboardComponent()->SetValueAsFloat(TEXT("PrevTargetDist"), _DefaultDist);

	return;
}

void UEnemyDetection::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* pController = OwnerComp.GetAIOwner();
	if (nullptr == pController)
		return;

	AMyTower* pTower = Cast<AMyTower>(pController->GetPawn());

	if (nullptr == pTower)
		return;

	float fDefaultRange = pTower->GetTowerInfo().fDetectRange;

	pController->GetBlackboardComponent()->SetValueAsBool(TEXT("AttackEnable"), pTower->GetAttackEnable());

	USphereComponent* pSphere = pTower->GetDetectSphere();
	if (nullptr == pSphere)
		return;

	TArray<AActor*> OverlapList;
	pSphere->GetOverlappingActors(OverlapList, TSubclassOf<AMonster>());
	//==========================================================================================================
	// 예외 1. 겹친 목록이 없으면 리셋 후 return
	if (0 == OverlapList.Num())
	{
		ResetTarget(pController, fDefaultRange);
		return;
	}

	
	m_pTarget = Cast<AMonster>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (nullptr != m_pTarget)
	{
		// 예외 2. 타겟이 존재하지만 죽은 상태인 경우 리셋
		if (EMON_STATE::DEAD == m_pTarget->GetState())
		{
			ResetTarget(pController, fDefaultRange);
		}
	}
	else
	{
		ResetTarget(pController, fDefaultRange);
	}

	// 현재 타워의 월드 위치
	Vec3 vTowerPos = pTower->GetActorLocation();
	vTowerPos.Z = 0.f;

	// 1. 타겟 지정이 필요한 경우
	if (nullptr == m_pTarget)
	{
		// 1.1. 감지 충돌체와 오버랩된 물체에 대한 검사 수행
		for (AActor* TargetIter : OverlapList)
		{
			// 1.1.1. 검출 대상이 죽은 상태이면 다음 반복 수행
			if (EMON_STATE::DEAD == Cast<AMonster>(TargetIter)->GetState())
				continue;

			float PrevCheckDist = pController->GetBlackboardComponent()->GetValueAsFloat(TEXT("PrevTargetDist"));
			// 1.1.2. 검출 대상과의 거리 체크
			{
				Vec3 vTargetPos = TargetIter->GetActorLocation();
				vTargetPos.Z = 0.f;

				float fCheckDist = Vec3::Distance(vTowerPos, vTargetPos);

				// 기본 감지거리 이내라면
				if (fCheckDist <= PrevCheckDist)
				{
					// 다운 캐스팅하여 타겟으로 설정
					m_pTarget = Cast<AMonster>(TargetIter);
					// 캐스팅 실패 시 다음 반복 수행
					if (nullptr == m_pTarget)
						continue;

					pController->GetBlackboardComponent()->SetValueAsFloat(TEXT("PrevTargetDist"), fCheckDist);
				}
			}
		}

		// 블랙 보드에 타겟 반영 및 반복 탈출
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), m_pTarget);
	}
	// 2. 타겟 지정이 이미 된 경우
	else
	{
		// 2.1. 타겟이 감지 범위를 벗어난 경우 리셋 후 리턴
		Vec3 vTargetPos = m_pTarget->GetActorLocation();
		vTargetPos.Z = 0.f;

		float fCheckDist = Vec3::Distance(vTowerPos, vTargetPos);
		if (fCheckDist > fDefaultRange)
		{
			UE_LOG(LogTemp, Warning, TEXT("Tower : (%f | %f | %f)   Target : (%f | %f | %f)   "),
				vTowerPos.X, vTowerPos.Y, vTowerPos.Z,
				vTargetPos.X, vTargetPos.Y, vTargetPos.Z)
			ResetTarget(pController, fDefaultRange);
			return;
		}
	}
}