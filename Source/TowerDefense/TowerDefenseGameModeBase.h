// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "global.h"

#include <blueprint/UserWidget.h>

#include "UI/MainHUD.h"
#include "UI/PlayerHUD.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TowerDefenseGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATowerDefenseGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ATowerDefenseGameModeBase();

private:
	TSubclassOf<UUserWidget>	m_MainHUDClass;
	UMainHUD* m_MainHUD;

public:
	UMainHUD* GetMainHUD() { return m_MainHUD; }
	void UpdatePlayHUD(uint8 _CurHP, int32 _CurCoin);
	void ToggleTowerSelect(bool _On);
	void ToggleTowerUpAndSell(bool _On);
	

	void SetGamePaused(bool _bIsPaused);
	void LooseGame();
	uint8 GetEnemyCount();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
