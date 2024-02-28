#pragma once

#include "../global.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* m_ProjectileMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* m_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* m_Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* m_Particle;

public:
	UProjectileMovementComponent* GetProjectile() { return m_ProjectileMovement; }
	UStaticMeshComponent* GetMesh() { return m_Mesh; }
	UBoxComponent* GetBox() { return m_Box; }
	UParticleSystemComponent* GetParticle() { return m_Particle; }

protected:
	void SetProjectile(UProjectileMovementComponent* _com) { m_ProjectileMovement = _com; }
	void SetMesh(UStaticMeshComponent* _com) { m_Mesh = _com; }
	void SetBox(UBoxComponent* _com) { m_Box = _com; }
	void SetParticle(UParticleSystemComponent* _com) { m_Particle = _com; }

public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// collision delegate
public:
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult);

};
