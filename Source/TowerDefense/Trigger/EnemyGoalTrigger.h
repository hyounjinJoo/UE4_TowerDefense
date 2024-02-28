// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EnemyGoalTrigger.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AEnemyGoalTrigger : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	AEnemyGoalTrigger();
	~AEnemyGoalTrigger();

public:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor);
};
