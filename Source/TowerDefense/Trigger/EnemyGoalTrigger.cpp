#include "EnemyGoalTrigger.h"
#include "../Monster/Normal/NormalMonster.h"
#include "../Player/MyCharacter.h"
#include "../TowerDefenseGameModeBase.h"

#include "../MyGameInstance.h"

AEnemyGoalTrigger::AEnemyGoalTrigger()
{
}

AEnemyGoalTrigger::~AEnemyGoalTrigger()
{
}

void AEnemyGoalTrigger::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &AEnemyGoalTrigger::BeginTrigger);
}

void AEnemyGoalTrigger::BeginTrigger(AActor* _TriggerActor, AActor* _OtherActor)
{
	// 노멀 몬스터인 경우
	ANormalMonster* NormalEnemy = Cast<ANormalMonster>(_OtherActor);
	if (nullptr == NormalEnemy)
		return;

	NormalEnemy->ChangeState(EMON_STATE::DEAD);

	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (!GI)
		return;

	GI->DecreasePlayerHP();

	if (0 >= GI->GetPlayerCurHP())
	{
		ATowerDefenseGameModeBase* GM = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if (!GM)
			return;

		GM->LooseGame();
	}
}
