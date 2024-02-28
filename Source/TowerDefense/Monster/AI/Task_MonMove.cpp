#include "Task_MonMove.h"

#include <Blueprint/AIBlueprintHelperLibrary.h>
#include <BehaviorTree/BlackboardComponent.h>

#include "../Normal/Normal_Rat.h"
#include "MonAIController.h"

UTask_MonMove::UTask_MonMove()
{
}

EBTNodeResult::Type UTask_MonMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonAIController* pAI = Cast<AMonAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pAI)
		return EBTNodeResult::Type::Failed;

	ANormal_Rat* pMonster = Cast<ANormal_Rat>(pAI->GetPawn());
	if (nullptr == pMonster)
		return EBTNodeResult::Type::Failed;

	//if (pMonster->IsUnStopable())
	//	return EBTNodeResult::Type::Failed;

	Vec3 vPos = pMonster->GetNextPatrolPos();
	vPos.Z = pMonster->GetActorLocation().Z;
	pAI->GetBlackboardComponent()->SetValueAsVector(FName(TEXT("NextPatrolPos")), vPos);

	// 다음 목적지를 향해서 이동한다
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(pAI, vPos);

	// 몬스터의 애님 상태를 무브로 바꾼다.
	pMonster->ChangeState(EMON_STATE::MOVE);

	bNotifyTick = 1;
	return EBTNodeResult::Type::InProgress;
}

void UTask_MonMove::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 몬스터의 속도가 0에 도달하면 목적지에 도착
	AMonAIController* pAI = Cast<AMonAIController>(OwnerComp.GetAIOwner());
	if (nullptr == pAI)
		return;

	ANormal_Rat* pMonster = Cast<ANormal_Rat>(pAI->GetPawn());
	if (nullptr == pMonster)
		return;

	// 목적지에 도착했는지 확인
	Vec3 vGoalPos = pAI->GetBlackboardComponent()->GetValueAsVector(FName(TEXT("NextPatrolPos")));
	Vec3 vMonPos = pMonster->GetActorLocation();
	float fDistance = Vec3::Distance(vGoalPos, vMonPos);
		
	if (EPathFollowingStatus::Idle == pAI->GetMoveStatus())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
	}
}