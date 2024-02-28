#include "MyGameInstance.h"

#include "Manager/EffectMgr.h"
#include "Player/MyCharacter.h"

UMyGameInstance::UMyGameInstance()
	: m_MonTable(nullptr)
	, m_TowerTable(nullptr)
{
	ConstructorHelpers::FObjectFinder<UDataTable> monTable(TEXT("DataTable'/Game/BlueprintClass/Monster/MonTable.MonTable'"));
	if (monTable.Succeeded())
	{
		m_MonTable = monTable.Object;		
	}

	ConstructorHelpers::FObjectFinder<UDataTable> towerTable(TEXT("DataTable'/Game/BlueprintClass/Tower/TowerInfo.TowerInfo'"));
	if (towerTable.Succeeded())
	{
		m_TowerTable = towerTable.Object;
	}
}

UMyGameInstance::~UMyGameInstance()
{
	UEffectMgr::Destroy();
}

const FMonInfo* UMyGameInstance::GetMonInfo(const FString& _RowName)
{
	FMonInfo* pMonInfo = m_MonTable->FindRow<FMonInfo>(FName(_RowName), TEXT(""));
	return pMonInfo;
}

const FTowerInfo* UMyGameInstance::GetTowerInfo(const FString& _RowName)
{
	FTowerInfo* pTowerInfo = m_TowerTable->FindRow<FTowerInfo>(FName(_RowName), TEXT(""));
	return pTowerInfo;
}

const FPlayerInfo* UMyGameInstance::GetPlayerInfo(const FString& _RowName)
{
	FPlayerInfo* pPlayerInfo = m_PlayerInfo->FindRow<FPlayerInfo>(FName(_RowName), TEXT(""));
	return pPlayerInfo;
}

void UMyGameInstance::DecreasePlayerHP()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		Player->DecreaseCurHP();
	}
}

void UMyGameInstance::IncreasePlayerHP()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		Player->IncreaseCurHP();
	}
}

uint8 UMyGameInstance::GetPlayerCurHP()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		return Player->GetCurHP();
	}

	return 0;
}

void UMyGameInstance::DecreasePlayerCoin(int32 _Coin)
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		Player->DecreaseCoin(_Coin);
	}
}

void UMyGameInstance::IncreasePlayerCoin(int32 _Coin)
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		Player->IncreaseCoin(_Coin);
	}
}

int32 UMyGameInstance::GetPlayerCoin()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (Player)
	{
		return Player->GetCoin();
	}

	return 0;
}
