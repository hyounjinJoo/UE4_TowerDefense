#pragma once

#include "../../global.h"

#include "CoreMinimal.h"
#include "../ProjectileBase.h"
#include "Missile.generated.h"

UCLASS()
class TOWERDEFENSE_API AMissile : public AProjectileBase
{
	GENERATED_BODY()
private:
	float	m_fAccTime;

public:
	// Sets default values for this actor's properties
	AMissile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit) override;
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult) override;

private:
	void CreateHitEffect();
};
