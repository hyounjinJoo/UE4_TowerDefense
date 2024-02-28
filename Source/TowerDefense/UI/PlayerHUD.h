// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <Components/TextBlock.h>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	UTextBlock* m_HP;
	UTextBlock* m_Coin;

public:
	void UpdateHP(uint8 _HP);
	void UpdateCoin(int32 _Coin);
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DT) override;
};
