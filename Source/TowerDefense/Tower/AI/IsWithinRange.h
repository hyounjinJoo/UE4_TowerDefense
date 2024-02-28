#pragma once

#include "../../global.h"

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "IsWithinRange.generated.h"

UENUM(BlueprintType)
enum class ERANGE_TYPE : uint8
{
	DETECTION,
	ATTACK,
};

UCLASS()
class TOWERDEFENSE_API UIsWithinRange : public UBTDecorator
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ERANGE_TYPE m_Type;

public:
	UIsWithinRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
