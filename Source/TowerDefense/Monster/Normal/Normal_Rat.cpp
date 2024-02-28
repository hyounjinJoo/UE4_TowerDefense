#include "Normal_Rat.h"

#include "../../MyGameInstance.h"

ANormal_Rat::ANormal_Rat()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		RatMesh(TEXT("SkeletalMesh'/Game/RPGMonsterWave02Polyart/Meshes/RatAssassinMesh.RatAssassinMesh'"));

	if (RatMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(RatMesh.Object);
		GetMesh()->GetRelativeTransform().SetScale3D(Vec3(0.6f));
	}

	ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimBlueprint(TEXT("AnimBlueprint'/Game/BlueprintClass/Monster/Normal/Rat/ABP_Rat.ABP_Rat_C'"));
	if (AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprint.Class);
	}

	SetUnStopable(false);
}

void ANormal_Rat::BeginPlay()
{
	Super::BeginPlay();

	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FMonInfo* pTableRow = pGameInst->GetMonInfo(TEXT("NormalRatEasy"));
		if (nullptr != pTableRow)
		{
			SetMonInfo(*pTableRow);
			GetCharacterMovement()->MaxWalkSpeed = pTableRow->fOriginMoveSpeed;
		}
	}

	SetState(EMON_STATE::MOVE);
}

void ANormal_Rat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANormal_Rat::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	if (ECC_GameTraceChannel4 == _OtherComp->GetCollisionObjectType())
	{
		ChangeState(EMON_STATE::HIT);
		FMonInfo info = GetMonInfo();
		info.fCurHP -= 10.f;
		SetMonInfo(info);
	}
}


void ANormal_Rat::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	if (ECC_GameTraceChannel4 == _OtherComp->GetCollisionObjectType())
	{
		ChangeState(EMON_STATE::HIT);
		FMonInfo info = GetMonInfo();
		info.fCurHP -= 10.f;
		SetMonInfo(info);
	}
}