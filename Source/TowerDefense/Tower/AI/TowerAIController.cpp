#include "TowerAIController.h"

#include "../MyTower.h"

ATowerAIController::ATowerAIController()
	: m_BehaviorTree(nullptr)
	, m_Blackboard(nullptr)
{

}

void ATowerAIController::OnPossess(APawn* _Tower)
{
	AAIController::OnPossess(_Tower);

	AMyTower* pTower = Cast<AMyTower>(_Tower);

	if (nullptr != pTower)
	{
		m_BehaviorTree = pTower->GetBehaviorTree();
		m_Blackboard = pTower->GetBlackboard();

		UseBlackboard(m_Blackboard, Blackboard);
		RunBehaviorTree(m_BehaviorTree);
	}
}

void ATowerAIController::OnUnPossess()
{
}