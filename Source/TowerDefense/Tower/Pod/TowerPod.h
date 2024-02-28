// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../global.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerPod.generated.h"

UCLASS()
class TOWERDEFENSE_API ATowerPod : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent*			m_Root;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent*		m_PodMesh;


	ETOWER_TYPE					m_PrevPreviewType;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent*		m_PreviewMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	UMaterialInstance*			m_PreviewMtrl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Info, meta = (AllowPrivateAccess = "true"))
	FTransform					m_TowerTransform;


	UPROPERTY(VisibleAnywhere)
	bool						m_bIsTowerInstall;

public:
	void SetPreviewVisibility(bool _isVisible) { m_PreviewMesh->SetVisibility(_isVisible); }
	void SetPreviewTower(ETOWER_TYPE _TowerType);

	void SetTowerTransform(FTransform _Transform) { m_TowerTransform = _Transform; }
	void SetTowerInstall(bool _isInstall) { m_bIsTowerInstall = _isInstall; }

	bool GetTowerInstalled() { return m_bIsTowerInstall; }
	void SpawnTower(ETOWER_TYPE _Type);
public:	
	// Sets default values for this actor's properties
	ATowerPod();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void OnClicked(UPrimitiveComponent* Target, FKey ButtonPressed);
};
