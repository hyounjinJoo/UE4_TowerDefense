#include "ProjectileBase.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetBox() && (nullptr == GetMesh()))
	{
		GetBox()->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
		GetBox()->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnBeginOverlap);
	}
	if (GetMesh())
	{
		GetMesh()->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
		GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::OnBeginOverlap);
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{

}

void AProjectileBase::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
}
