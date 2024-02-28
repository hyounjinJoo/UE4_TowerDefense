#pragma once

#include "../global.h"
#include "Monster.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class TOWERDEFENSE_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*	m_StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*>			m_PatrolPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FSpawnInfo				m_SpawnInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMonster>	m_SpawnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	uint8					m_uCurSpawnCount;

	bool					m_bIsSpawnUse;
	float					m_fSpawnTimeRemain;

public:	
	// Sets default values for this actor's properties
	ASpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetSpawnType(TSubclassOf<AMonster> _SpawnType) { m_SpawnType = _SpawnType; }
	void SetSpawnInfo(FSpawnInfo _Info) { m_SpawnInfo = _Info; }
	FSpawnInfo GetSpawnInfo() { return m_SpawnInfo; }

private:
	void Spawn();

};
