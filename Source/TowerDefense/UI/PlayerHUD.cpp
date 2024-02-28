// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_HP = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPVal")));
	m_HP->SetText(FText::FromString(FString::Printf(TEXT("%d"), 0)));
	m_Coin = Cast<UTextBlock>(GetWidgetFromName(TEXT("CoinVal")));
	m_Coin->SetText(FText::FromString(FString::FromInt(0)));
}

void UPlayerHUD::NativeTick(const FGeometry& Geometry, float DT)
{
	Super::NativeTick(Geometry, DT);
}

void UPlayerHUD::UpdateHP(uint8 _HP)
{
	if(m_HP)
		m_HP->SetText(FText::FromString(FString::Printf(TEXT("%u"), _HP)));
}

void UPlayerHUD::UpdateCoin(int32 _Coin)
{
	if(m_Coin)
		m_Coin->SetText(FText::FromString(FString::FromInt(_Coin)));

}
