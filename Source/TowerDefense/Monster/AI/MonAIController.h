#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MonAIController.generated.h"

UCLASS()
class TOWERDEFENSE_API AMonAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMonAIController();

	// BehaviorTreeComponent
	// BlackboardComponent
	UBehaviorTree*		m_BehaviorTree;

	UBlackboardData*	m_Blackboard;

public:
	virtual void OnPossess(APawn* _mon) override;
	virtual void OnUnPossess() override;
};
