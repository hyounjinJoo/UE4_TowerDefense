#include "MyCharacter.h"

#include "../TowerDefenseGameModeBase.h"

// Sets default values
AMyCharacter::AMyCharacter()
	: m_PrevHP(0)
	, m_PrevCoin(0)
	, m_fScreenMargine(0.9f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������ �� ����, ���� ���� ����, �浹 ��Ȱ��ȭ, �⺻ ���� ����
	m_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	m_Arm->SetupAttachment(GetMesh());
	m_Arm->bDoCollisionTest = false;
	m_Arm->TargetArmLength = 1200.f;
	m_Arm->SetRelativeRotation(FRotator(-50, 0, 0));

	// ī�޶� ���� �� ���� ���� ����
	m_Cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Cam->SetupAttachment(m_Arm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	m_PlayerCtrl = Cast<APlayerController>(GetController());

	m_Info.iCoin = 2000;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (m_PrevHP != m_Info.uCurHP || m_PrevCoin != m_Info.iCoin)
	{
		ATowerDefenseGameModeBase* GM = Cast<ATowerDefenseGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		GM->UpdatePlayHUD(m_Info.uCurHP, m_Info.iCoin);
	}

	m_PrevHP = m_Info.uCurHP;
	m_PrevCoin = m_Info.iCoin;

	MoveCharacterMouseDir();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveFront"), this, &AMyCharacter::MoveFront);
	PlayerInputComponent->BindAxis(TEXT("MoveSide"), this, &AMyCharacter::MoveSide);
	PlayerInputComponent->BindAxis(TEXT("Zoom"), this, &AMyCharacter::Zoom);
}

void AMyCharacter::MoveCharacterMouseDir()
{
	if(nullptr == m_PlayerCtrl)
		m_PlayerCtrl = Cast<APlayerController>(GetController());

	float X = 0.f, Y = 0.f;
	int32 resX = 0, resY = 0;
	m_PlayerCtrl->GetMousePosition(X, Y);
	m_PlayerCtrl->GetViewportSize(resX, resY);

	// ���콺 X,Y �������� ȭ�� �߾����κ��� �־��� ���� ��
	float fRatioX = fabs(X - (float)(resX / 2)) / (float)(resX / 2);
	float fRatioY = fabs(Y - (float)(resY / 2)) / (float)(resY / 2);

	// ȭ�� �߽����κ��� ���콺�� 60% �̳��� ��ġ�� ó�� X
	if (m_fScreenMargine > fRatioX && m_fScreenMargine > fRatioY)
		return;

	if (1.f <= m_fScreenMargine)
		return;

	float MinSpeed = 10.f;
	float MaxSpeed = 50.f;

	// ȭ�� �߽����κ��� 60% ���콺�� �־����� ������ ���� ����
	if (m_fScreenMargine <= fRatioX)
	{
		float fDirX = 0.f;
		if (X < (float)(resX / 2))
		{
			// �������� �̵� ����
			fDirX = -1.f;
		}
		else
		{
			// ���������� �̵� ����
			fDirX = 1.f;
		}

		// �߽� ȭ�� �ʰ����� 60% ~ 100% ���� �ӵ��� �ʴ� 100 ~ 500�� �ӵ��� ������ �ȴ�.		
		float Alpha = (fRatioX - m_fScreenMargine) / (1.0f - m_fScreenMargine);
		if (Alpha < 0.f) Alpha = 0.f;
		if (Alpha > 1.f) Alpha = 1.f;

		float fCurSpeed = FMath::Lerp(50.f, 200.f, Alpha);
		
		AddMovementInput(FVector(fDirX, 0.f, 0.f), fCurSpeed * GetWorld()->GetDeltaSeconds());
	}

	if (m_fScreenMargine <= fRatioY)
	{
		float fDirY = 0.f;
		if (Y < (float)(resY / 2))
		{
			// �������� ȸ��
			fDirY = -1.f;
		}
		else
		{
			// ���������� ȸ��
			fDirY = 1.f;
		}

		// �߽� ȭ�� �ʰ����� 60% ~ 100% ���� �ӵ��� �ʴ� 100 ~ 500�� �ӵ��� ������ �ȴ�.
		float Alpha = (fRatioY - m_fScreenMargine) / (1.0f - m_fScreenMargine);
		if (Alpha < 0.f) Alpha = 0.f;
		if (Alpha > 1.f) Alpha = 1.f;

		float fCurSpeed = FMath::Lerp(50.f, 200.f, Alpha);
		
		AddMovementInput(FVector(0.f, fDirY, 0.f), fCurSpeed * GetWorld()->GetDeltaSeconds());
	}
}

void AMyCharacter::MoveFront(float _fScale)
{	
	Vec3 Location = GetActorLocation();
	Location += GetActorForwardVector() * 5.f * _fScale;

	AddMovementInput(GetActorForwardVector(), 5.f * _fScale);
}

void AMyCharacter::MoveSide(float _fScale)
{
	Vec3 Location = GetActorLocation();
	Location += GetActorRightVector() * 5.f * _fScale;

	AddMovementInput(GetActorRightVector(), 5.f * _fScale);
}

#define MIN_ARM_LENGTH 600.f
#define MAX_ARM_LENGTH 1200.f
void AMyCharacter::Zoom(float _fScale)
{
	float fDT = GetWorld()->GetDeltaSeconds();
	m_Arm->TargetArmLength += _fScale * 40.f;

	if (m_Arm->TargetArmLength > MAX_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MAX_ARM_LENGTH;
	}
	else if (m_Arm->TargetArmLength < MIN_ARM_LENGTH)
	{
		m_Arm->TargetArmLength = MIN_ARM_LENGTH;
	}	
}

void AMyCharacter::OnBeginOverlap(UPrimitiveComponent* _PrimitiveComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, int32 _OtherBodyIndex, bool _bFromSweep, const FHitResult& _SweepResult)
{
	LOG(Warning, TEXT("Overlap Character"))
}

void AMyCharacter::OnHit(UPrimitiveComponent* _HitComponent, AActor* _OtherActor, UPrimitiveComponent* _OtherComp, FVector _NormalImpulse, const FHitResult& Hit)
{
	LOG(Warning, TEXT("Hit Character"))
}