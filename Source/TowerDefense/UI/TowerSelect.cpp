// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerSelect.h"

#include "../Tower/Cannon.h"
#include "../MyGameInstance.h"

void UTowerSelect::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeBtn();


}

void UTowerSelect::NativeTick(const FGeometry& Geometry, float DT)
{
	Super::NativeTick(Geometry, DT);
}

void UTowerSelect::BtnCannonOnClicked()
{
	if (!m_TargetPod)
		return;

	if (m_TargetPod->GetTowerInstalled())
		return;


	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
		return;
	
	int32 BuyPrice = GI->GetTowerInfo(FString("CannonLv1"))->iBuyPrice;
	
	if (BuyPrice > GI->GetPlayerCoin())
		return;

	GI->DecreasePlayerCoin(BuyPrice);

	m_TargetPod->SpawnTower(ETOWER_TYPE::CANNON);
}

void UTowerSelect::BtnMortarOnClicked()
{
	if (!m_TargetPod)
		return;

	if (m_TargetPod->GetTowerInstalled())
		return;
}

void UTowerSelect::BtnDebuffOnClicked()
{
	if (!m_TargetPod)
		return;

	if (m_TargetPod->GetTowerInstalled())
		return;
}

void UTowerSelect::BtnBuffOnClicked()
{
	if (!m_TargetPod)
		return;

	if (m_TargetPod->GetTowerInstalled())
		return;
}

void UTowerSelect::BtnCannonOnHovered()
{
	if (!m_TargetPod)
		return;

	m_TargetPod->SetPreviewTower(ETOWER_TYPE::CANNON);
	m_TargetPod->SetPreviewVisibility(true);
}

void UTowerSelect::BtnMortarOnHovered()
{
	if (!m_TargetPod)
		return;

	//m_TargetPod->SetPreviewTower(ETOWER_TYPE::CANNON);
	//m_TargetPod->SetPreviewVisibility(true);
}

void UTowerSelect::BtnDebuffOnHovered()
{
	if (!m_TargetPod)
		return;

	//m_TargetPod->SetPreviewTower(ETOWER_TYPE::CANNON);
	//m_TargetPod->SetPreviewVisibility(true);
}

void UTowerSelect::BtnBuffOnHovered()
{
	if (!m_TargetPod)
		return;

	//m_TargetPod->SetPreviewTower(ETOWER_TYPE::CANNON);
	//m_TargetPod->SetPreviewVisibility(true);
}

void UTowerSelect::BtnCancelOnClicked()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UTowerSelect::BtnOnUnHovered()
{
	m_TargetPod->SetPreviewVisibility(false);
}

void UTowerSelect::InitializeBtn()
{
	m_BtnCannon = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Cannon")));

	if (IsValid(m_BtnCannon))
	{
		m_BtnCannon->OnClicked.AddDynamic(this, &UTowerSelect::BtnCannonOnClicked);
		m_BtnCannon->OnHovered.AddDynamic(this, &UTowerSelect::BtnCannonOnHovered);
		m_BtnCannon->OnUnhovered.AddDynamic(this, &UTowerSelect::BtnOnUnHovered);
	}

	m_BtnMortar = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Mortar")));

	if (IsValid(m_BtnMortar))
	{
		m_BtnMortar->OnClicked.AddDynamic(this, &UTowerSelect::BtnMortarOnClicked);
		m_BtnMortar->OnHovered.AddDynamic(this, &UTowerSelect::BtnMortarOnHovered);
		m_BtnMortar->OnUnhovered.AddDynamic(this, &UTowerSelect::BtnOnUnHovered);
	}

	m_BtnDebuff = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Debuff")));

	if (IsValid(m_BtnDebuff))
	{
		m_BtnDebuff->OnClicked.AddDynamic(this, &UTowerSelect::BtnDebuffOnClicked);
		m_BtnDebuff->OnHovered.AddDynamic(this, &UTowerSelect::BtnDebuffOnHovered);
		m_BtnDebuff->OnUnhovered.AddDynamic(this, &UTowerSelect::BtnOnUnHovered);
	}

	m_BtnBuff = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Buff")));

	if (IsValid(m_BtnBuff))
	{
		m_BtnBuff->OnClicked.AddDynamic(this, &UTowerSelect::BtnBuffOnClicked);
		m_BtnBuff->OnHovered.AddDynamic(this, &UTowerSelect::BtnBuffOnHovered);
		m_BtnBuff->OnUnhovered.AddDynamic(this, &UTowerSelect::BtnOnUnHovered);
	}

	m_BtnCancel = Cast<UButton>(GetWidgetFromName(TEXT("Btn_Cancel")));

	if (IsValid(m_BtnCancel))
	{
		m_BtnCancel->OnClicked.AddDynamic(this, &UTowerSelect::BtnCancelOnClicked);
	}
	
}