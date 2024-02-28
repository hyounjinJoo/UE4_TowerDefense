// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void UMainHUD::NativeConstruct()
{
	Super::NativeConstruct();

	m_PlayerHUD = Cast<UPlayerHUD>(GetWidgetFromName(TEXT("PlayerHUD")));
	m_TowerSelect = Cast<UTowerSelect>(GetWidgetFromName(TEXT("TowerSelect")));
	m_TowerUpAndSell = Cast<UTowerUpAndSell>(GetWidgetFromName(TEXT("TowerUpandSell")));

	m_TowerSelect->SetVisibility(ESlateVisibility::Hidden);
	m_TowerUpAndSell->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUD::NativeTick(const FGeometry& Geometry, float DT)
{
	Super::NativeTick(Geometry, DT);
}

void UMainHUD::ToggleTowerSelect(bool _On)
{
	if (_On)
		m_TowerSelect->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else
		m_TowerSelect->SetVisibility(ESlateVisibility::Hidden);
}

void UMainHUD::ToggleTowerUpAndSell(bool _On)
{
	if (_On)
		m_TowerUpAndSell->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	else
		m_TowerUpAndSell->SetVisibility(ESlateVisibility::Hidden);
}