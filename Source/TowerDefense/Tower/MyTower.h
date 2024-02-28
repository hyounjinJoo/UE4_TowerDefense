#pragma once

#include <BehaviorTree/BehaviorTree.h>
#include <BehaviorTree/BlackboardData.h>

#include "../global.h"

#include "Pod/TowerPod.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyTower.generated.h"

class UMyAnimInstance;

UCLASS()
class TOWERDEFENSE_API AMyTower : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent*			m_Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent*		m_TowerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USphereComponent*			m_DetectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBehaviorTree*				m_BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBlackboardData*			m_Blackboard;

	UPROPERTY(VisibleAnywhere)
	bool						m_bIsNeedToUpgrade;

	UPROPERTY(VisibleAnywhere)
	bool						m_bIsNeedToRemove;

	// 가장 가까이 인지한 몬스터의 방향을 가리키도록 한다.

	UPROPERTY(VisibleAnywhere)
	float						m_fDirection;

	UMyAnimInstance*			m_AnimInst;

	bool						m_bAttackEnable;
	float						m_fAttackInterval;
	float						m_fRemainInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ETOWER_STATE				m_eState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FTowerInfo					m_Info;

	UPROPERTY(VisibleAnywhere)
	ATowerPod*					m_InstalledPod;

protected:
	ETOWER_TYPE					m_eTowerType;

public:
	UBehaviorTree* GetBehaviorTree() { return m_BehaviorTree; }
	UBlackboardData* GetBlackboard() { return m_Blackboard; }

	void SetUpgrade(bool _b) { m_bIsNeedToUpgrade = _b; }
	bool IsNeedToUpgrade() { return m_bIsNeedToUpgrade; }
	void SetRemove(bool _b) { m_bIsNeedToRemove = _b; }
	bool IsNeedToRemove() { return m_bIsNeedToRemove; }

	void SetTowerInfo(const FTowerInfo& _info) { m_Info = _info; }
	ETOWER_STATE GetState() { return m_eState; }
	void ChangeState(ETOWER_STATE _eNextState);
	void SetTowerPod(ATowerPod* _pod) { m_InstalledPod = _pod; }
	ATowerPod* GetTowerPod() { return m_InstalledPod; }

	void SetDirection(float _f) { m_fDirection = _f; }
	float GetDirection() { return m_fDirection; }

	void SetAttackEnable(bool _b) { m_bAttackEnable = _b; }
	bool GetAttackEnable() { return m_bAttackEnable; }

	float GetAttackInterval() { return m_fAttackInterval; }
	float GetAttackSpeed() { return m_Info.iAttackCount; }

protected:
	void SetBehaviorTree(UBehaviorTree* _Tree) { m_BehaviorTree = _Tree; }
	void SetBlackboard(UBlackboardData* _board) { m_Blackboard = _board; }

	void SetTowerType(ETOWER_TYPE _TowerType) { m_eTowerType = _TowerType; }
	void SetDetectSphereSize(float _Size)
	{
		m_DetectSphere->SetSphereRadius(_Size);
	}

	USkeletalMeshComponent* GetMesh() { return m_TowerMesh; }
	uint8 GetTowerLv() { return m_Info.uLv; }
	ETOWER_TYPE GetTowerType() { return m_eTowerType; }

	void SetAttackInterval(int _iAttackCount)
	{
		if (0 == _iAttackCount)
		{
			m_fAttackInterval = 10.f;
		}
		else
		{
			m_fAttackInterval = 1.f / (float)_iAttackCount;
		}
	}
public:
	USphereComponent* GetDetectSphere() { return m_DetectSphere; }
	const FTowerInfo& GetTowerInfo() { return m_Info; }
	void SetTowerLv(uint8 _uLv) { m_Info.uLv = _uLv; }
	void SetMeshMtrl(UMaterialInstance* _Mtrl) { m_TowerMesh->SetMaterial(0, _Mtrl); }

	UMyAnimInstance* GetAnimInst() { return m_AnimInst; }

public:
	// Sets default values for this pawn's properties
	AMyTower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Notify
public:
	virtual void Fire() {}
	virtual void DestroyProcess() {}
	
	// Anim Montage play
protected:
	virtual void Install() {}
	virtual void Idle() {}
	virtual void Attack() {}
	virtual void NeedUpgrade() {}
	virtual void Upgrade() {}
	virtual void RemoveWithUpgarde() {}
	virtual void Remove() {}


public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* Target, FKey ButtonPressed);
};
