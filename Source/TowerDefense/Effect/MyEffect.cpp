#include "MyEffect.h"

#include "../Manager/LevelStreamMgr.h"

AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Particle =  CreateDefaultSubobject<UParticleSystemComponent>("ParticleComponent");
	SetRootComponent(m_Particle);
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();
		
	FSoftObjectPath assetPath = nullptr;

	UParticleSystem* ParticleAsset = Cast<UParticleSystem>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(m_eType)));
	if (nullptr != ParticleAsset)
	{
		m_Particle->SetTemplate(ParticleAsset);
		m_Particle->OnSystemFinished.AddDynamic(this, &AMyEffect::OnFinish);
	}

}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyEffect::OnFinish(UParticleSystemComponent* _Particle)
{
	Destroy();
}