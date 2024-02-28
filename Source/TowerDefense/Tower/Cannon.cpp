#include "Cannon.h"

#include "../Effect/MyEffect.h"
#include "../Manager/EffectMgr.h"
#include "../Projectile/Missile/Missile.h"
#include "../MyGameInstance.h"

#include "../Manager/LevelStreamMgr.h"

ACannon::ACannon()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		CannonMesh(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv01/CannonLv1Mesh.CannonLv1Mesh'"));

	if (CannonMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CannonMesh.Object);
	}

	ConstructorHelpers::FClassFinder<UAnimInstance>
		AnimBlueprint(TEXT("AnimBlueprint'/Game/BlueprintClass/Tower/Cannon/ABP_CannonLv1.ABP_CannonLv1_C'"));
	if (AnimBlueprint.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimBlueprint.Class);
	}

	SetTowerLv(1);
	SetTowerType(ETOWER_TYPE::CANNON);
	ChangeState(ETOWER_STATE::INSTALL);

	SetAttackInterval(GetTowerInfo().iAttackCount);
}

// Called when the game starts or when spawned
void ACannon::BeginPlay()
{
	Super::BeginPlay();

	uint8 CurLv = GetTowerLv();
	switch (CurLv)
	{
	case 4:
		SetTowerTable("CannonLv4");
		break;
	case 3:
		SetTowerTable("CannonLv3");
		break;
	case 2:
		SetTowerTable("CannonLv2");
		break;
	case 1:
	default:
		SetTowerTable("CannonLv1");
		break;
	}
	SetAttackInterval(GetTowerInfo().iAttackCount);
	SetDetectSphereSize(GetTowerInfo().fDetectRange);
}

// Called every frame
void ACannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsNeedToUpgrade())
	{
		Upgrade();
	}
}

void ACannon::Fire()
{
	FName fnSocket = FName(TEXT("Bone_002socket"));
	FTransform tEffectTrans = GetMesh()->GetSocketTransform(fnSocket);

	Vec3 vScale = Vec3(3.f);
	tEffectTrans.SetScale3D(vScale);
	
	UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::MUZZLEFLASH, tEffectTrans, GetLevel());
	ACannon::SpawnProjectile(tEffectTrans);

	if ((uint8)4 == GetTowerLv())
	{
		fnSocket = FName(TEXT("Bone_002socket1"));
		tEffectTrans = GetMesh()->GetSocketTransform(fnSocket);
		
		tEffectTrans.SetScale3D(vScale);

		UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::MUZZLEFLASH, tEffectTrans, GetLevel());
		ACannon::SpawnProjectile(tEffectTrans);
	}
}

void ACannon::SetTowerTable(const FString& _TowerStr)
{
	UMyGameInstance* pGameInst = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (nullptr != pGameInst)
	{
		const FTowerInfo* pTableRow = pGameInst->GetTowerInfo(_TowerStr);
		if (nullptr != pTableRow)
		{
			SetTowerInfo(*pTableRow);
		}
	}
}

void ACannon::SpawnProjectile(FTransform _trans)
{
	Vec3 vPos = _trans.GetLocation();
	vPos.Z -= 20.f;
	Vec3 vForward = _trans.GetRotation().Rotator().Vector();

	FActorSpawnParameters SpawnParam = {};
	// 생성될 레벨
	SpawnParam.OverrideLevel = GetLevel();
	// 충돌될 지점이 어디인지에 따라 스폰을 할 지에 대한 것을 나타냄
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 지연 스폰.
	SpawnParam.bDeferConstruction = true;

	AMissile* pMissile = GetWorld()->SpawnActor<AMissile>(m_Projectile
		, vPos
		, vForward.Rotation(), SpawnParam);

	// BeginPlay 호출
	pMissile->FinishSpawning(pMissile->GetTransform());
}

void ACannon::ChangeTower(int _CurLv)
{
	USkeletalMesh* CannonMesh = nullptr;
	UAnimBlueprint* CannonABP = nullptr;

	switch (_CurLv)
	{
	case 1:
		{
			CannonMesh = Cast<USkeletalMesh>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_SKEL::CANNON1)));
			CannonABP = Cast<UAnimBlueprint>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_ABP::CANNON1)));
		}
		break;
	case 2:
		{
			CannonMesh = Cast<USkeletalMesh>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_SKEL::CANNON2)));
			CannonABP = Cast<UAnimBlueprint>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_ABP::CANNON2)));
		}
		break;
	case 3:
		{
			CannonMesh = Cast<USkeletalMesh>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_SKEL::CANNON3)));
			CannonABP = Cast<UAnimBlueprint>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_ABP::CANNON3)));
		}
		break;
	case 4:
		{
			CannonMesh = Cast<USkeletalMesh>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_SKEL::CANNON4)));
			CannonABP = Cast<UAnimBlueprint>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_ABP::CANNON4)));
		}
	default:
		break;
	}

	if (nullptr != CannonMesh
		&& nullptr != CannonABP)
	{
		GetMesh()->SetAnimInstanceClass(nullptr);
		GetMesh()->SetSkeletalMesh(CannonMesh);
		GetMesh()->SetAnimInstanceClass(CannonABP->GeneratedClass);
	}
}

void ACannon::DestroyProcess()
{
	Destroy();
}

void ACannon::Install()
{
	uint8 CurLv = GetTowerLv();
	switch (CurLv)
	{
	case 4:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv4");
		break;
	case 3:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv3");
		break;
	case 2:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv2");
		break;
	case 1:
		ChangeTower(CurLv);
		SetTowerTable("CannonLv1");
	default:
		break;
	}

	SetAttackInterval(GetTowerInfo().iAttackCount);
	SetDetectSphereSize(GetTowerInfo().fDetectRange);

	SetUpgrade(false);
	SetRemove(false);
}

void ACannon::Idle()
{
}

void ACannon::Attack()
{
	
}

void ACannon::NeedUpgrade()
{
	SetUpgrade(true);
}

void ACannon::Upgrade()
{
	if (ETOWER_TYPE::CANNON != GetTowerType())
	{
		return;
	}

	uint8 CurLv = GetTowerLv();

	ETOWER_STATE eState = GetState();

	if(ETOWER_STATE::NEEDUPGRADE != eState)
		return;

	SetTowerLv(++CurLv);
	ChangeState(ETOWER_STATE::INSTALL);
}

void ACannon::RemoveWithUpgarde()
{
}

void ACannon::Remove()
{
}

