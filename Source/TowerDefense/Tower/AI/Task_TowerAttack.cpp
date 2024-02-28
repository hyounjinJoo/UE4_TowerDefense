#include "Task_TowerAttack.h"

#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>

#include "TowerAIController.h"
#include "../../Monster/Monster.h"
#include "../MyTower.h"

UTask_TowerAttack::UTask_TowerAttack()
{

}

EBTNodeResult::Type UTask_TowerAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ATowerAIController* pController = Cast<ATowerAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pController)
		return EBTNodeResult::Type::Failed;

	AMyTower* pTower = Cast<AMyTower>(pController->GetPawn());
	if (nullptr == pTower)
		return EBTNodeResult::Type::Failed;

	// 공격 상태로 바꾼다.
	pTower->ChangeState(ETOWER_STATE::ATTACK);

	return EBTNodeResult::Type();
}

void UTask_TowerAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
}

EBTNodeResult::Type UTask_TowerAttack::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::AbortTask(OwnerComp, NodeMemory);;
}
