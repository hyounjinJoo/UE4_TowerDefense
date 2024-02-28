// Copyright Epic Games, Inc. All Rights Reserved.


#include "TowerDefenseGameModeBase.h"

#include "MyGameInstance.h"
#include "Player/MyCharacter.h"

#include "manager/LevelStreamMgr.h"

ATowerDefenseGameModeBase::ATowerDefenseGameModeBase()
{
	//DefaultPawnClass = AMyCharacter::StaticClass();

	ConstructorHelpers::FClassFinder<APawn>
		MainCharacterClass(TEXT("Blueprint'/Game/BlueprintClass/BPC_Player.BPC_Player_C'"));

	if (MainCharacterClass.Succeeded())
	{
		DefaultPawnClass = MainCharacterClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> MainHUD(TEXT("WidgetBlueprint'/Game/BlueprintClass/Widget/MainHUD.MainHUD_C'"));
	if (MainHUD.Succeeded())
	{
		m_MainHUDClass = MainHUD.Class;
	}
}

void ATowerDefenseGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	m_MainHUD = Cast<UMainHUD>(CreateWidget(GetWorld(), m_MainHUDClass));

	if (nullptr == m_MainHUD)
		return;

	m_MainHUD->AddToViewport();

	// InputMode
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	//FInputModeUIOnly mode;
	//FInputModeGameOnly mode;
	FInputModeGameAndUI mode;

	Controller->SetInputMode(mode);
	Controller->bShowMouseCursor = true; // ������ ���콺 Ŀ���� ���̰� �Ѵ�.
	Controller->bEnableClickEvents = true;	// ���콺 Ŭ�� �̺�Ʈ�� �߻��ϵ��� �Ѵ�.
	Controller->bEnableMouseOverEvents = true; // ���콺 ���� �̺�Ʈ�� �߻��ϵ��� �Ѵ�.
	ULevelStreamMgr::GetInst(GetWorld())->LoadAssetAsync();	
}

void ATowerDefenseGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ATowerDefenseGameModeBase::UpdatePlayHUD(uint8 _CurHP, int32 _CurCoin)
{
	UPlayerHUD* pPlayerHUD = m_MainHUD->GetPlayerHUD();

	pPlayerHUD->UpdateHP(_CurHP);
	pPlayerHUD->UpdateCoin(_CurCoin);
}

void ATowerDefenseGameModeBase::ToggleTowerSelect(bool _On)
{
	m_MainHUD->ToggleTowerSelect(_On);
}

void ATowerDefenseGameModeBase::ToggleTowerUpAndSell(bool _On)
{
	m_MainHUD->ToggleTowerUpAndSell(_On);
}

void ATowerDefenseGameModeBase::SetGamePaused(bool _bIsPaused)
{
	APlayerController* const Controller = GetWorld()->GetFirstPlayerController();
	if (nullptr != Controller)
	{
		Controller->SetPause(_bIsPaused);
	}
}

void ATowerDefenseGameModeBase::LooseGame()
{
	SetGamePaused(true);

}

uint8 ATowerDefenseGameModeBase::GetEnemyCount()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMonster::StaticClass(), FoundActors);

	return FoundActors.Num();
}