#pragma once

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>

#include "../global.h"
#include "../MyStruct.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class TOWERDEFENSE_API AMonster : public ACharacter
{
	GENERATED_BODY()

private:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UWidgetComponent* m_WidgetComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* m_BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBlackboardData* m_Blackboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FMonInfo		m_Info;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	EMON_STATE		m_eState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State, meta = (AllowPrivateAccess = "true"))
	TArray<FVector>	m_PatrolPoints;

	int8			m_NextPatrolIdx;

	float			m_PrevHP;
	bool			bIsUnStopable;

public:
	// Sets default values for this character's properties
	AMonster();

public:
	UBehaviorTree* GetBehaviorTree() { return m_BehaviorTree; }
	UBlackboardData* GetBlackboard() { return m_Blackboard; }
	//UWidgetComponent* GetWidgetComponent() { return m_WidgetComponent; }
	Vec3 GetNextPatrolPos();

protected:
	void SetMonInfo(const FMonInfo& _info) { m_Info = _info; }
	void SetBehaviorTree(UBehaviorTree* _Tree) { m_BehaviorTree = _Tree; }
	void SetBlackboard(UBlackboardData* _board) { m_Blackboard = _board; }
	void SetState(EMON_STATE _eState) { m_eState = _eState; }

public:
	EMON_STATE GetState() { return m_eState; }
	const FMonInfo& GetMonInfo() { return m_Info; }
	void SetDamage(float _fDamage) { m_Info.fCurHP -= _fDamage; }
	bool IsUnStopable() { return bIsUnStopable; }
	void SetUnStopable(bool _bState) { bIsUnStopable = _bState; }
	void AddPatrolPoint(Vec3 _vPosition) { m_PatrolPoints.Add(_vPosition); }

public:
	virtual bool ChangeState(EMON_STATE _eNextState) { return true; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌 알림 함수
public:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);
};
