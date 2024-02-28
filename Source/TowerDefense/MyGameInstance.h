// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster/Monster.h"
#include "Tower/MyTower.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class TOWERDEFENSE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	UDataTable*		m_MonTable;
	UDataTable*		m_TowerTable;
	UDataTable*		m_PlayerInfo;

public:
	const FMonInfo* GetMonInfo(const FString& _RowName);
	const FTowerInfo* GetTowerInfo(const FString& _RowName);
	const FPlayerInfo* GetPlayerInfo(const FString& _RowName);

public:
	void DecreasePlayerHP();
	void IncreasePlayerHP();
	uint8 GetPlayerCurHP();

	void DecreasePlayerCoin(int32 _Coin);
	void IncreasePlayerCoin(int32 _Coin);
	int32 GetPlayerCoin();

public:
	UMyGameInstance();
	~UMyGameInstance();
	
};
