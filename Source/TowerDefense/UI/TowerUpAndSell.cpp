// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerUpAndSell.h"

#include "../MyGameInstance.h"
#include "../Tower/Pod/TowerPod.h"

void UTowerUpAndSell::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeBtn();
}

void UTowerUpAndSell::NativeTick(const FGeometry& Geometry, float DT)
{
	Super::NativeTick(Geometry, DT);
}

void UTowerUpAndSell::InitializeBtn()
{
	m_BtnUpgrade = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Upgrade")));

	if (IsValid(m_BtnUpgrade))
	{
		m_BtnUpgrade->OnClicked.AddDynamic(this, &UTowerUpAndSell::BtnUpgradeOnClicked);
		m_BtnUpgrade->OnHovered.AddDynamic(this, &UTowerUpAndSell::BtnUpgradeOnHovered);
		m_BtnUpgrade->OnUnhovered.AddDynamic(this, &UTowerUpAndSell::BtnOnUnHovered);
	}

	m_BtnSell = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Sell")));

	if (IsValid(m_BtnSell))
	{
		m_BtnSell->OnClicked.AddDynamic(this, &UTowerUpAndSell::BtnSellOnClicked);
		m_BtnSell->OnHovered.AddDynamic(this, &UTowerUpAndSell::BtnSellOnHovered);
		m_BtnSell->OnUnhovered.AddDynamic(this, &UTowerUpAndSell::BtnOnUnHovered);
	}

	m_BtnCancel = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Cancel")));

	if (IsValid(m_BtnCancel))
	{
		m_BtnCancel->OnClicked.AddDynamic(this, &UTowerUpAndSell::BtnCancelOnClicked);
		m_BtnCancel->OnHovered.AddDynamic(this, &UTowerUpAndSell::BtnCancelOnHovered);
		m_BtnCancel->OnUnhovered.AddDynamic(this, &UTowerUpAndSell::BtnOnUnHovered);
	}
}

void UTowerUpAndSell::BtnUpgradeOnClicked()
{
	if (!m_TargetTower)
		return;


	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
		return;

	int32 BuyPrice = GI->GetTowerInfo(FString("CannonLv1"))->iBuyPrice;

	if (BuyPrice > GI->GetPlayerCoin())
		return;

	GI->DecreasePlayerCoin(BuyPrice);

	m_TargetTower->SetAttackEnable(false);

	m_TargetTower->ChangeState(ETOWER_STATE::REMOVEWITHUPGRADE);
	m_TargetTower = nullptr;

	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTowerUpAndSell::BtnSellOnClicked()
{
	if (!m_TargetTower)
		return;

	// Tower의 Pod를 가져올 수 있도록 멤버변수 추가할 것.
	//if (m_TargetTower->GetTowerInstalled())
	//	return;

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
		return;

	int32 SellPrice = m_TargetTower->GetTowerInfo().iSellPrice;

	GI->IncreasePlayerCoin(SellPrice);

	m_TargetTower->SetAttackEnable(false);
	m_TargetTower->GetTowerPod()->SetTowerInstall(false);
	m_TargetTower->ChangeState(ETOWER_STATE::REMOVE);
	m_TargetTower = nullptr;

	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTowerUpAndSell::BtnCancelOnClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTowerUpAndSell::BtnUpgradeOnHovered()
{
}

void UTowerUpAndSell::BtnSellOnHovered()
{
}


void UTowerUpAndSell::BtnCancelOnHovered()
{
}

void UTowerUpAndSell::BtnOnUnHovered()
{
}
