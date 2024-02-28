#include "StartMapMode.h"

AStartMapMode::AStartMapMode()
{
	ConstructorHelpers::FClassFinder<UUserWidget> StartHUD(TEXT("WidgetBlueprint'/Game/BlueprintClass/Widget/StartHUD.StartHUD_C'"));
	if (StartHUD.Succeeded())
	{
		m_StartHUDClass = StartHUD.Class;
	}
}

void AStartMapMode::BeginPlay()
{
	Super::BeginPlay();

	// HUD 화면에 등록
	m_StartHUD = Cast<UUserWidget>(CreateWidget(GetWorld(), m_StartHUDClass));

	if (nullptr == m_StartHUD)
		return;

	m_StartHUD->AddToViewport();

	// InputMode 설정
	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	FInputModeUIOnly mode;

	Controller->SetInputMode(mode);
	Controller->bShowMouseCursor = true; // 언제나 마우스 커서가 보이게 한다.
}