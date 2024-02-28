#include "MyTower.h"

#include "AI/TowerAIController.h"
#include "../MyAnimInstance.h"
#include "../Monster/Monster.h"
#include "../TowerDefenseGameModeBase.h"

// Sets default values
AMyTower::AMyTower()
	: m_bIsNeedToUpgrade(false)
	, m_bAttackEnable(true)
	, m_fAttackInterval(0.f)
	, m_fRemainInterval(0.f)
	, m_eState(ETOWER_STATE::IDLE)
	, m_Info{}
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(m_Root);

	m_TowerMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TowerMesh"));
	m_TowerMesh->SetupAttachment(m_Root);

	m_DetectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DetectSphere"));
	m_DetectSphere->SetupAttachment(m_Root);
	m_DetectSphere->SetCollisionProfileName(TEXT("EnemyDetect"));

	// 사용 할 AIController 클래스 지정
	AIControllerClass = ATowerAIController::StaticClass();

	// AIController 빙의 방식 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 사용 할 행동트리
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/BlueprintClass/Tower/AI/BT_Tower.BT_Tower'"));
	if (BT.Succeeded())
	{
		SetBehaviorTree(BT.Object);
	}
	// 사용 할 블랙보드
	ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/BlueprintClass/Tower/AI/BB_Tower.BB_Tower'"));

	if (BB.Succeeded())
	{
		SetBlackboard(BB.Object);
	}

	m_TowerMesh->OnClicked.AddDynamic(this, &AMyTower::OnClicked);
}

void AMyTower::ChangeState(ETOWER_STATE _eNextState)
{
	if (m_eState == _eNextState)
		return;

	if (_eNextState == ETOWER_STATE::ATTACK
		&& (m_bIsNeedToUpgrade || m_bIsNeedToRemove))
		return;

	m_eState = _eNextState;

	switch (_eNextState)
	{
	case ETOWER_STATE::INSTALL:
	{
		Install();
	}
		break;
	case ETOWER_STATE::IDLE:
	{
		Idle();
	}
		break;
	case ETOWER_STATE::ATTACK:
	{
		if (m_bAttackEnable)
		{
			Attack();
			m_bAttackEnable = false;
		}
	}
		break;
	case ETOWER_STATE::NEEDUPGRADE:
	{
		NeedUpgrade();
	}
		break;
	case ETOWER_STATE::REMOVEWITHUPGRADE:
	{
		m_bIsNeedToUpgrade = true;
		RemoveWithUpgarde();
	}
		break;
	case ETOWER_STATE::REMOVE:
	{
		m_bIsNeedToRemove = true;
		m_InstalledPod = nullptr;
		Remove();
	}
		break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void AMyTower::BeginPlay()
{
	Super::BeginPlay();
	
	m_AnimInst = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	ChangeState(ETOWER_STATE::INSTALL);
}

// Called every frame
void AMyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_bAttackEnable && !m_bIsNeedToUpgrade && !m_bIsNeedToRemove)
	{
		m_fRemainInterval -= DeltaTime;

		if (m_fRemainInterval <= 0.f)
		{
			m_fRemainInterval = m_fAttackInterval;
			m_bAttackEnable = true;
		}
	}
}

void AMyTower::OnClicked(UPrimitiveComponent* Target, FKey ButtonPressed)
{
	UE_LOG(LogTemp, Warning, TEXT("Tower Clicked"))
	ATowerDefenseGameModeBase* GM = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	if (!GM)
		return;

	GM->GetMainHUD()->SetTowerUpAndSellTarget(this);
	GM->GetMainHUD()->ToggleTowerUpAndSell(true);
}
