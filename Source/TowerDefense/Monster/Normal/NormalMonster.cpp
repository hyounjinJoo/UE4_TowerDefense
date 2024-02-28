// Fill out your copyright notice in the Description page of Project Settings.


#include "NormalMonster.h"

#include "../../MyGameInstance.h"

ANormalMonster::ANormalMonster()
{	
	// 사용 할 행동트리
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/BlueprintClass/Monster/Normal/BT_NormalMon.BT_NormalMon'"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
	// 사용 할 블랙보드
	ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/BlueprintClass/Monster/Normal/BB_NormalMon.BB_NormalMon'"));

	if (BB.Succeeded())
	{
		SetBlackboard(BB.Object);
	}
}

bool ANormalMonster::ChangeState(EMON_STATE _eNextState)
{
	EMON_STATE eCurState = GetState();

	if (EMON_STATE::DEAD == eCurState)
		return false;

	if (EMON_STATE::HIT == _eNextState)
	{
		SetUnStopable(false);
	}

	if (IsUnStopable() || eCurState == _eNextState)
		return false;

	SetState(_eNextState);

	switch (GetState())
	{
	case EMON_STATE::IDLE:
		SetState(EMON_STATE::MOVE);
		break;
	case EMON_STATE::MOVE:
		break;
	case EMON_STATE::HIT:
		break;
	case EMON_STATE::DEAD:
		ANormalMonster::DeadProcess();
		break;
	default:
		break;
	}

	return true;
}
void ANormalMonster::DeadProcess()
{
	GetMovementComponent()->StopMovementImmediately();
	UMyGameInstance* GI = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int32 Coin = GetMonInfo().iCoin;
	
	if (0 == Coin)
		Coin = 0;

	GI->IncreasePlayerCoin(Coin);
	SetUnStopable(true);
	GetMesh()->SetSimulatePhysics(true);
	SetLifeSpan(2);
}

void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ANormalMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}