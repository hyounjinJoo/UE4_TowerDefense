// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <Engine/AssetManager.h>

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyEffect.generated.h"

UCLASS()
class TOWERDEFENSE_API AMyEffect : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_Particle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	EEFFECT_TYPE			  m_eType;

public:
	void SetEffectType(EEFFECT_TYPE _eType) { m_eType = _eType; }

public:	
	// Sets default values for this actor's properties
	AMyEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnFinish(UParticleSystemComponent* _Particle);

};
