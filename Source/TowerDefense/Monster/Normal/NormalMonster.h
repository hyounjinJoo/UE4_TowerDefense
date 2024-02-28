#pragma once

#include "../../global.h"

#include "CoreMinimal.h"
#include "../Monster.h"
#include "NormalMonster.generated.h"

UCLASS()
class TOWERDEFENSE_API ANormalMonster : public AMonster
{
	GENERATED_BODY()

public:
	ANormalMonster();

public:
	virtual bool ChangeState(EMON_STATE _eNextState) override;

private:
	void DeadProcess();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 충돌 알림 함수
public:
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult) {};
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit) {};
};
