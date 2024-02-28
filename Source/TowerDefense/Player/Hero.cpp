#include "Hero.h"

AHero::AHero()
{
	// 사용할 Mesh를 레퍼런스로 찾아 로딩 전용 클래스에 설정받음.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		HeroMesh(TEXT("SkeletalMesh'/Game/Meshes/hand.hand'"));

	if (HeroMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(HeroMesh.Object);
	}

	//GetMesh()->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
}

void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
