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

	// ���� üũ Ÿ�� �˾Ƴ���
	AMyTower* pTower = Cast<AMyTower>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == pTower)
		return false;

	const FTowerInfo& info = pTower->GetTowerInfo();

	// Ÿ���� ��Ʈ�ѷ��� ���ؼ� �����忡 ��ϵ� ��ǥ�� �˾Ƴ���
	ATowerAIController* pController = Cast<ATowerAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return false;

	AMonster* pMonster = Cast<AMonster>(pController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (nullptr == pMonster)
		return false;

	// Ÿ���� ������ �Ÿ��� ���Ѵ�.
	float fDistance = Vec3::Distance(pTower->GetActorLocation(), pMonster->GetActorLocation());

	// ���� ���� Ÿ�Կ� ���� �Ÿ��� �ش� �����̳��� �ִ��� üũ
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
