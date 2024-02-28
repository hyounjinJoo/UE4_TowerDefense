// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "../MyAnimInstance.h"
#include "../Projectile/ProjectileBase.h"

#include <Engine/AssetManager.h>

#include "CoreMinimal.h"
#include "MyTower.h"
#include "Cannon.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ACannon : public AMyTower
{
	GENERATED_BODY()
// 아래 인터벌 변수는 테스트 변수니까 지워야 한다.
private:
	float m_fAttackInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase>	m_Projectile;

	TSharedPtr<FStreamableHandle>	m_Handle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<USkeletalMesh>	m_MeshPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<USoundBase>		m_SoundPath;


public:
	ACannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 콜백
public:
	virtual void Fire() override;
	virtual void DestroyProcess() override;

private:
	void SetTowerTable(const FString& _TowerStr);
	void SpawnProjectile(FTransform _trans);
	void ChangeTower(int _CurLv);

protected:
	virtual void Install() override;
	virtual void Idle() override;
	virtual void Attack() override;
	virtual void NeedUpgrade() override;
	virtual void Upgrade() override;
	virtual void RemoveWithUpgarde() override;
	virtual void Remove() override;
};
