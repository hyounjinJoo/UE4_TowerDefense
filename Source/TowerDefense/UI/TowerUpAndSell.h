#pragma once

#include "../global.h"

#include <Components/Button.h>

#include "../Tower/MyTower.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerUpAndSell.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UTowerUpAndSell : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& Geometry, float DT) override;

private:
	UButton* m_BtnUpgrade;
	UButton* m_BtnSell;
	UButton* m_BtnCancel;

	AMyTower* m_TargetTower;

public:
	void SetTargetTower(AMyTower* _target)
	{
		if (_target)
			m_TargetTower = _target;
	}

private:
	void InitializeBtn();

private:
	// Button OnClicked Delegate.
	UFUNCTION()
		void BtnUpgradeOnClicked();
	UFUNCTION()
		void BtnSellOnClicked();
	UFUNCTION()
		void BtnCancelOnClicked();

	// Button OnHovered Delegate.
	UFUNCTION()
		void BtnUpgradeOnHovered();
	UFUNCTION()
		void BtnSellOnHovered();
	UFUNCTION()
		void BtnCancelOnHovered();

	// Button OnUnHovered Delegate.
	UFUNCTION()
		void BtnOnUnHovered();
};
