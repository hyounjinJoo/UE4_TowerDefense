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
	// ���� 1. ��ģ ����� ������ ���� �� return
	if (0 == OverlapList.Num())
	{
		ResetTarget(pController, fDefaultRange);
		return;
	}

	
	m_pTarget = Cast<AMonster>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (nullptr != m_pTarget)
	{
		// ���� 2. Ÿ���� ���������� ���� ������ ��� ����
		if (EMON_STATE::DEAD == m_pTarget->GetState())
		{
			ResetTarget(pController, fDefaultRange);
		}
	}
	else
	{
		ResetTarget(pController, fDefaultRange);
	}

	// ���� Ÿ���� ���� ��ġ
	Vec3 vTowerPos = pTower->GetActorLocation();
	vTowerPos.Z = 0.f;

	// 1. Ÿ�� ������ �ʿ��� ���
	if (nullptr == m_pTarget)
	{
		// 1.1. ���� �浹ü�� �������� ��ü�� ���� �˻� ����
		for (AActor* TargetIter : OverlapList)
		{
			// 1.1.1. ���� ����� ���� �����̸� ���� �ݺ� ����
			if (EMON_STATE::DEAD == Cast<AMonster>(TargetIter)->GetState())
				continue;

			float PrevCheckDist = pController->GetBlackboardComponent()->GetValueAsFloat(TEXT("PrevTargetDist"));
			// 1.1.2. ���� ������ �Ÿ� üũ
			{
				Vec3 vTargetPos = TargetIter->GetActorLocation();
				vTargetPos.Z = 0.f;

				float fCheckDist = Vec3::Distance(vTowerPos, vTargetPos);

				// �⺻ �����Ÿ� �̳����
				if (fCheckDist <= PrevCheckDist)
				{
					// �ٿ� ĳ�����Ͽ� Ÿ������ ����
					m_pTarget = Cast<AMonster>(TargetIter);
					// ĳ���� ���� �� ���� �ݺ� ����
					if (nullptr == m_pTarget)
						continue;

					pController->GetBlackboardComponent()->SetValueAsFloat(TEXT("PrevTargetDist"), fCheckDist);
				}
			}
		}

		// �� ���忡 Ÿ�� �ݿ� �� �ݺ� Ż��
		pController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), m_pTarget);
	}
	// 2. Ÿ�� ������ �̹� �� ���
	else
	{
		// 2.1. Ÿ���� ���� ������ ��� ��� ���� �� ����
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