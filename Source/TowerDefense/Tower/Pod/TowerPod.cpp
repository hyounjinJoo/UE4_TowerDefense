#include "TowerPod.h"

#include "../../TowerDefenseGameModeBase.h"
#include "../../UI/MainHUD.h"

#include "../MyTower.h"

#include "../Cannon.h"

#include "../../Manager/LevelStreamMgr.h"

// Sets default values
ATowerPod::ATowerPod()
{
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_Root);

	m_PodMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PodMesh"));
	m_PodMesh->SetupAttachment(m_Root);

	m_PreviewMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PreviewMesh"));
	m_PreviewMesh->SetupAttachment(m_Root);

	ConstructorHelpers::FObjectFinder<UStaticMesh>
		PodMesh(TEXT("StaticMesh'/Game/LowPolyMedievalConstructions/Meshes/SM_Plate_1.SM_Plate_1'"));

	if (PodMesh.Succeeded())
	{
		m_PodMesh->SetStaticMesh(PodMesh.Object);
	}

	m_PodMesh->OnClicked.AddDynamic(this, &ATowerPod::OnClicked);

	ConstructorHelpers::FObjectFinder<USkeletalMesh>
		CannonMesh(TEXT("SkeletalMesh'/Game/FattyTurret/Cannon/Lv01/CannonLv1Mesh.CannonLv1Mesh'"));

	if (CannonMesh.Succeeded())
	{
		m_PreviewMesh->SetSkeletalMesh(CannonMesh.Object);
	}	
}

// Called when the game starts or when spawned
void ATowerPod::BeginPlay()
{
	Super::BeginPlay();
	
	FVector SpawnLoc = GetActorLocation();
	SpawnLoc.Z += 20.f;

	FRotator SpawnRot = GetActorRotation();

	m_TowerTransform = FTransform();
	m_TowerTransform.SetLocation(SpawnLoc);
	m_TowerTransform.SetRotation(FQuat(SpawnRot));
	m_TowerTransform.SetScale3D(FVector(1.f));

	UMaterialInstance* Mtrl = LoadObject<UMaterialInstance>(nullptr, TEXT("MaterialInstanceConstant'/Game/Material/Mtrl_TowerHologram_Inst.Mtrl_TowerHologram_Inst'"));
	if (Mtrl)
	{
		m_PreviewMtrl = Mtrl;
		m_PreviewMesh->SetMaterial(0, m_PreviewMtrl);
	}
}

// Called every frame
void ATowerPod::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATowerPod::OnClicked(UPrimitiveComponent* Target, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Mesh Clicked"))

		if (m_bIsTowerInstall)
		{

		}
		else
		{
			ATowerDefenseGameModeBase* GM = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

			if (!GM)
				return;

			GM->GetMainHUD()->SetTowerSelectTarget(this);
			GM->GetMainHUD()->ToggleTowerSelect(true);
		}
}

void ATowerPod::SetPreviewTower(ETOWER_TYPE _TowerType)
{
	if (_TowerType == m_PrevPreviewType)
		return;

	USkeletalMesh* PreviewMesh = nullptr;

	switch (_TowerType)
	{
	case ETOWER_TYPE::CANNON:
		PreviewMesh = Cast<USkeletalMesh>(ULevelStreamMgr::GetInst(GetWorld())->FindAsset(Function::EnumToName(ETOWER_SKEL::CANNON1)));
		break;
	case ETOWER_TYPE::MORTAR:
		return;
		break;
	case ETOWER_TYPE::TOWER3:
		return;
		break;
	case ETOWER_TYPE::TOWER4:
		return;
		break;
	default:
		return;
	}

	if (PreviewMesh)
	{
		m_PreviewMesh->SetSkeletalMesh(PreviewMesh);
		m_PreviewMesh->SetMaterial(0, m_PreviewMtrl);
		m_PrevPreviewType = _TowerType;
	}
}

void ATowerPod::SpawnTower(ETOWER_TYPE _Type)
{
	FActorSpawnParameters SpawnParam = {};
	SpawnParam.OverrideLevel = GetLevel();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	static FString TowerBPPath = FString();

	TSubclassOf<AActor> BPSubClass = nullptr;

	switch (_Type)
	{
	case ETOWER_TYPE::CANNON:
		TowerBPPath = TEXT("Blueprint'/Game/BlueprintClass/Tower/Cannon/BP_Cannon.BP_Cannon_C'");
		BPSubClass = Cast<UClass>(StaticLoadObject(UObject::StaticClass(), nullptr, *TowerBPPath));
		break;
	case ETOWER_TYPE::MORTAR:
		TowerBPPath = TEXT("Blueprint'/Game/BlueprintClass/Tower/Cannon/BP_Cannon.BP_Cannon_C'");
		BPSubClass = Cast<UClass>(StaticLoadObject(UObject::StaticClass(), nullptr, *TowerBPPath));
		break;
	case ETOWER_TYPE::TOWER3:
		TowerBPPath = TEXT("Blueprint'/Game/BlueprintClass/Tower/Cannon/BP_Cannon.BP_Cannon_C'");
		BPSubClass = Cast<UClass>(StaticLoadObject(UObject::StaticClass(), nullptr, *TowerBPPath));
		break;
	case ETOWER_TYPE::TOWER4:
		TowerBPPath = TEXT("Blueprint'/Game/BlueprintClass/Tower/Cannon/BP_Cannon.BP_Cannon_C'");
		BPSubClass = Cast<UClass>(StaticLoadObject(UObject::StaticClass(), nullptr, *TowerBPPath));
		break;
	default:
		TowerBPPath = TEXT("Blueprint'/Game/BlueprintClass/Tower/Cannon/BP_Cannon.BP_Cannon_C'");
		BPSubClass = Cast<UClass>(StaticLoadObject(UObject::StaticClass(), nullptr, *TowerBPPath));
		break;
	}

	AMyTower* pTower = GetWorld()->SpawnActor<AMyTower>(BPSubClass, m_TowerTransform, SpawnParam);

	pTower->FinishSpawning(pTower->GetTransform());
	m_bIsTowerInstall = true;
	pTower->SetTowerPod(this);

	ATowerDefenseGameModeBase* GM = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GM)
		return;

	GM->GetMainHUD()->SetTowerSelectTarget(nullptr);
	GM->GetMainHUD()->ToggleTowerSelect(false);
}