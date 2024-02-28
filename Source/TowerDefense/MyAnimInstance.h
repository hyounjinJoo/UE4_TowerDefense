// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "global.h"

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_fAttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	m_fDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_bAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool	m_bFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ETOWER_STATE	m_eState;


public:
	void SetAttack(bool _b) { m_bAttack = _b; }
	bool GetAttack() { return m_bAttack; }
	void SetFire(bool _b) { m_bFire = _b; }
	bool GetFire() { return m_bFire; }

public:
	UMyAnimInstance();

	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float _fDT) override;

	UFUNCTION()
	void AnimNotify_AttackEnd();
	UFUNCTION()
	void AnimNotify_Fire();
	UFUNCTION()
	void AnimNotify_InstallEnd();
	UFUNCTION()
	void AnimNotify_RemoveEnd();
};
