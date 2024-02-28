#include "IsWithinRange.h"

#include <BehaviorTree/BlackboardComponent.h>
#include "TowerAIController.h"
#include "../../Monster/Monster.h"
#include "../MyTower.h"

UIsWithinRange::UIsWithinRange()
{

}

bool UIsWithinRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bReturn = false;

	// 범위 체크 타워 알아내기
	AMyTower* pTower = Cast<AMyTower>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == pTower)
		return false;

	const FTowerInfo& info = pTower->GetTowerInfo();

	// 타워의 컨트롤러를 통해서 블랙보드에 등록된 목표물 알아내기
	ATowerAIController* pController = Cast<ATowerAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return false;

	AMonster* pMonster = Cast<AMonster>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == pMonster)
		return false;

	// 타워와 몬스터의 거리를 구한다.
	float fDistance = Vec3::Distance(pTower->GetActorLocation(), pMonster->GetActorLocation());

	// 비교할 범위 타입에 따라서 거리가 해당 범위이내에 있는지 체크
	if (ERANGE_TYPE::DETECTION == m_Type)
	{
		if (fDistance < info.fDetectRange)
		{
			Vec3 vTargetDir = pMonster->GetActorLocation() - pTower->GetActorLocation();
			vTargetDir.Z = 0.f;
			vTargetDir.Normalize();

			FRotator fRot = FRotationMatrix::MakeFromX(vTargetDir).Rotator();
			pTower->SetDirection(fRot.Yaw);

			bReturn = true;
		}
		else
		{
			pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
			bReturn = false;
		}
	}
	else if (ERANGE_TYPE::ATTACK == m_Type)
	{
		if (fDistance < info.fAttackRange)
		{
			Vec3 vTargetDir = pMonster->GetActorLocation() - pTower->GetActorLocation();
			vTargetDir.Z = 0.f;
			vTargetDir.Normalize();

			FRotator fRot = FRotationMatrix::MakeFromX(vTargetDir).Rotator();
			pTower->SetDirection(fRot.Yaw);

			bReturn = true;
		}
		else
		{
			pController->GetBlackboardComponent()->ClearValue(TEXT("Target"));
			bReturn = false;
		}
	}

	return bReturn;
}
