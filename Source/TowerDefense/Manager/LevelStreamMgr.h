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
	// ���� ������ �ҷ����� ���� ����
	TArray<FAssetData>	m_AssetData;

	TMap<FName, UObject*>			m_mapAssets; // �ε� �Ϸ�� ���ҽ� ���	

	// ��ƼŬ �񵿱� �ε� ���
	UPROPERTY(Config)
	TArray<FAssetPathInfo>			m_arrPath;	// ini ���Ͽ��� �ʱ�ȭ �޴� �ε� ���
	TSharedPtr<FStreamableHandle>	m_AssetHandle;	// �񵿱� �ε� �ڵ�

public:
	void LoadDataFromFolder(FString _strFolderPath);
	void LoadAssetAsync();

	UObject* FindAsset(FName _Name);

private:
	void Convert(TArray<FAssetPathInfo>& _arrPathInfo, TArray<UObject*>& _arrAssets);
	void OnComplete();
};
