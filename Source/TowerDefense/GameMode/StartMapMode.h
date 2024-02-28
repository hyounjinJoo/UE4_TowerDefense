// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <blueprint/UserWidget.h>

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartMapMode.generated.h"

/**
 *
 */
UCLASS()
class TOWERDEFENSE_API AStartMapMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	TSubclassOf<UUserWidget>	m_StartHUDClass;
	UUserWidget* m_StartHUD;

public:
	AStartMapMode();


public:
	virtual void BeginPlay() override;
};
