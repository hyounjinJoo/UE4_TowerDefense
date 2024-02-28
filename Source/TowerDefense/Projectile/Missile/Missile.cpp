#include "Missile.h"

#include "../../Manager/EffectMgr.h"

AMissile::AMissile()
{
	// ������Ʈ ����
	SetMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Missile")));
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/FattyTurret/Projectile/Bullet02.Bullet02'"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetStaticMesh(MeshAsset.Object);
		SetRootComponent(GetMesh());
	}
	else
	{
		SetBox(CreateDefaultSubobject<UBoxComponent>(TEXT("Box")));
		SetRootComponent(GetBox());
	}

	// ��ƼŬ ������Ʈ ���� �� ���� ����
	SetParticle(CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle")));
	ConstructorHelpers::FObjectFinder<UParticleSystem> particleAsset(TEXT("ParticleSystem'/Game/LowPolyVFX/Particles/P_SmokeTrail_01.P_SmokeTrail_01'"));
	if (particleAsset.Succeeded())
	{
		GetParticle()->SetTemplate(particleAsset.Object);
	}

	if (nullptr != GetMesh())
	{
		GetParticle()->SetupAttachment(GetMesh());
	}
	else
	{
		GetParticle()->SetupAttachment(GetBox());
	}

	// ����ü ������Ʈ ����� Mesh�� ����
	
	if (nullptr != GetMesh())
	{
		GetProjectile()->SetUpdatedComponent(GetMesh());
		GetMesh()->SetCollisionProfileName(TEXT("TowerProjectile"));
	}
	else
	{
		GetProjectile()->SetUpdatedComponent(GetBox());
		GetBox()->SetCollisionProfileName(TEXT("TowerProjectile"));
	}
}

void AMissile::BeginPlay()
{
	Super::BeginPlay();
}

void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fAccTime += DeltaTime;

	if (3.f <= m_fAccTime)
	{
		AMissile::CreateHitEffect();
		Destroy();
	}
}

void AMissile::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	Super::OnHit(_HitComponent, _OtherActor, _OtherComp, _NormalImpulse, Hit);

	// ��� 1
	//AMonster* pMon = Cast<AMonster>(_OtherActor);
	//if (nullptr pMon)
	//	return;

	// ���2
	// �θ� ��ü�� FName�� �����Ͽ� �̸��� ���ڿ��� �����ϰ� ���� ���� �� ���ڿ��� �ش� ��ü�� ���� �̸� ����
	// �̿� ���� ���ڿ��� ó��
	// 
	// ���3 ���ڿ� ��
	//if(_OtherActor->GetName() == TEXT("Monster"))

	AMissile::CreateHitEffect();
	Destroy();
}

void AMissile::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	Super::OnBeginOverlap(_PrimitiveComponent, _OtherActor, _OtherComp, _OtherBodyIndex, _bFromSweep, _SweepResult);

	AMissile::CreateHitEffect();
	Destroy();
}

void AMissile::CreateHitEffect()
{
	UEffectMgr::GetInst(GetWorld())->CreateEffect(EEFFECT_TYPE::HIT, GetMesh()->GetRelativeTransform(), GetLevel());
}
