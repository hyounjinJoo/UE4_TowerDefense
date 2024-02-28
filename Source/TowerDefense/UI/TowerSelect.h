// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../global.h"

#include <Components/Button.h>

#include "../Tower/Pod/TowerPod.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerSelect.generated.h"

UCLASS()
class TOWERDEFENSE_API UTowerSelect : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DT) override;

private:
	UButton* m_BtnCannon;
	UButton* m_BtnMortar;
	UButton* m_BtnDebuff;
	UButton* m_BtnBuff;
	UButton* m_BtnCancel;

	ATowerPod* m_TargetPod;

public:
	void SetTargetPod(ATowerPod* _target)
	{
		if (_target)
			m_TargetPod = _target;
	}

private:
	void InitializeBtn();
	AActor* GetTowerPod();

private:
	UFUNCTION()
	void BtnCannonOnClicked();
	UFUNCTION()
	void BtnMortarOnClicked();
	UFUNCTION()
	void BtnDebuffOnClicked();
	UFUNCTION()
	void BtnBuffOnClicked();
	UFUNCTION()
	void BtnCannonOnHovered();
	UFUNCTION()
	void BtnMortarOnHovered();
	UFUNCTION()
	void BtnDebuffOnHovered();
	UFUNCTION()
	void BtnBuffOnHovered();
	UFUNCTION()
	void BtnCancelOnClicked();
	UFUNCTION()
	void BtnOnUnHovered();
};
