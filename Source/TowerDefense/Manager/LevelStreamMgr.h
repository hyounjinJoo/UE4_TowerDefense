#pragma once

#include "../global.h"

#include <Engine\AssetManager.h>

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelStreamMgr.generated.h"

USTRUCT()
struct FAssetPathInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName			Name;

	UPROPERTY(EditAnywhere)
	FSoftObjectPath Path;
};

UCLASS(Config = Game)
class TOWERDEFENSE_API ULevelStreamMgr : public UObject
{
	GENERATED_BODY()
private:
	ULevelStreamMgr();
	~ULevelStreamMgr();

private:
	static ULevelStreamMgr* m_This;
	static UWorld* m_World;

public:
	static ULevelStreamMgr* GetInst(UWorld* _world);
	static void Destroy();

private:
	// 폴더 단위로 불러오는 에셋 정보
	TArray<FAssetData>	m_AssetData;

	TMap<FName, UObject*>			m_mapAssets; // 로딩 완료된 리소스 목록	

	// 파티클 비동기 로딩 목록
	UPROPERTY(Config)
	TArray<FAssetPathInfo>			m_arrPath;	// ini 파일에서 초기화 받는 로딩 목록
	TSharedPtr<FStreamableHandle>	m_AssetHandle;	// 비동기 로딩 핸들

public:
	void LoadDataFromFolder(FString _strFolderPath);
	void LoadAssetAsync();

	UObject* FindAsset(FName _Name);

private:
	void Convert(TArray<FAssetPathInfo>& _arrPathInfo, TArray<UObject*>& _arrAssets);
	void OnComplete();
};
