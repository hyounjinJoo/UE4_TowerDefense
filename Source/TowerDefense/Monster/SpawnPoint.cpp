// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
	: m_SpawnInfo{}
	, m_uCurSpawnCount(0)
	, m_fSpawnTimeRemain(0.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(m_StaticMeshComponent);

	m_StaticMeshComponent->SetCollisionProfileName(TEXT("SpawnArea"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereMesh.Succeeded())
	{
		m_StaticMeshComponent->SetStaticMesh(SphereMesh.Object);
	}
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_uCurSpawnCount < m_SpawnInfo.uSpawnNum
		&& 0.f <= m_fSpawnTimeRemain)
	{
		m_fSpawnTimeRemain -= DeltaTime;

		if (0.f >= m_fSpawnTimeRemain)
		{
			m_fSpawnTimeRemain = m_SpawnInfo.fSpawnInterval;

			ASpawnPoint::Spawn();
		}
	}
}

void ASpawnPoint::Spawn()
{
	if (nullptr == m_SpawnType || m_bIsSpawnUse)
	{
		return;
	}

	FActorSpawnParameters SpawnParam = {};
	SpawnParam.OverrideLevel = GetLevel();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	Vec3 vSpawnPointLocation = GetActorLocation();
	vSpawnPointLocation.Z = 109.f;

	Vec3 vDir = Vec3(0.f);

	AMonster* pMonster = GetWorld()->SpawnActor<AMonster>(m_SpawnType, FTransform(vDir.Rotation(), vSpawnPointLocation), SpawnParam);

	// 초기화 관련 호출
	// 몬스터가 순찰해야 하는 포인트들을 알려 줌	
	for (int j = 0; j < m_PatrolPoints.Num(); ++j)
	{
		//int idx = j % m_PatrolPoints.Num();
		int idx = j;
		pMonster->AddPatrolPoint(m_PatrolPoints[idx]->GetActorLocation());
	}

	// BeginPlay 호출
	pMonster->FinishSpawning(pMonster->GetTransform());

	++m_uCurSpawnCount;
}

