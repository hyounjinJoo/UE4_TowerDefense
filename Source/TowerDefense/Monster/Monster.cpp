#include "Monster.h"

#include "AI/MonAIController.h"

// Sets default values
AMonster::AMonster()
	: m_eState(EMON_STATE::IDLE)
	, m_NextPatrolIdx(-1)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 사용 할 AIController 클래스 지정
	AIControllerClass = AMonAIController::StaticClass();

	// AIController 빙의 방식 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 충돌 프로파일 설정
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyType"));
	
	m_Info = {};
}

Vec3 AMonster::GetNextPatrolPos()
{
	if (m_PatrolPoints.Num() == 0)
	{
		return GetActorLocation();
	}

	++m_NextPatrolIdx;
	if (m_PatrolPoints.Num() <= m_NextPatrolIdx)
	{
		m_NextPatrolIdx = m_PatrolPoints.Num() - 1;
	}

	return m_PatrolPoints[m_NextPatrolIdx];
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMonster::OnHit);
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_PrevHP != m_Info.fCurHP)
	{
	}

	m_PrevHP = m_Info.fCurHP;

	if (0.f >= m_Info.fCurHP)
	{
		ChangeState(EMON_STATE::DEAD);
	}
}

void AMonster::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{

}

void AMonster::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{

}