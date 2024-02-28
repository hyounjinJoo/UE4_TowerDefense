// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <Components/DecalComponent.h>

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class TOWERDEFENSE_API AMyCharacter 
	: public ACharacter
{
	GENERATED_BODY()

private:
	USkeletalMesh* m_SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCameraComponent*		m_Cam;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent*	m_Arm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerController*		m_PlayerCtrl;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32					m_ScreenSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32					m_ScreenSizeY;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float					m_fScreenMargine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FPlayerInfo				m_Info;

	uint8					m_PrevHP;
	int32					m_PrevCoin;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void MoveCharacterMouseDir();

protected:
	void SetSkeletalMesh(USkeletalMesh* _mesh) { m_SkeletalMesh = _mesh; }

public:
	void MoveFront(float _fScale);
	void MoveSide(float _fScale);
	void Zoom(float _fScale);
	APlayerController* GetPlayerController() { return m_PlayerCtrl; }

	void DecreaseCurHP() {
		if (0 < m_Info.uCurHP)
			--(m_Info.uCurHP);
	}
	void IncreaseCurHP() {
		if (m_Info.uCurHP < m_Info.uMaxHP)
		++(m_Info.uCurHP); 
	}

	uint8 GetCurHP() { return m_Info.uCurHP; }

	void DecreaseCoin(int32 _Coin) {
		m_Info.iCoin -= _Coin;

		if (0 > m_Info.iCoin)
			m_Info.iCoin = 0;
	}
	void IncreaseCoin(int32 _Coin) {
		if ((int64)_Coin + m_Info.iCoin > INT32_MAX)
			m_Info.iCoin = INT32_MAX;
		else
			m_Info.iCoin += _Coin;
	}

	int32 GetCoin() { return m_Info.iCoin; }
	const FPlayerInfo& GetInfo() { return m_Info; }	

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);
};
