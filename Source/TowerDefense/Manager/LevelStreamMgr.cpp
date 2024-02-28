// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStreamMgr.h"

#include <Engine/ObjectLibrary.h>

ULevelStreamMgr* ULevelStreamMgr::m_This = nullptr;
UWorld* ULevelStreamMgr::m_World = nullptr;

ULevelStreamMgr::ULevelStreamMgr()
{
}

ULevelStreamMgr::~ULevelStreamMgr()
{
}

ULevelStreamMgr* ULevelStreamMgr::GetInst(UWorld* _world)
{
	if (nullptr == m_This)
	{
		// ���� �ش�.
		// ������ ȣ�� �� HeapMemory�� NewObject�� ��ӹ��� UEffectMgr ��ü 1���� �����Ѵ�.
		// ���ÿ� NewObject�� ��ӹ������ν� G.C�� ����� �ȴ�.
		m_This = NewObject<ULevelStreamMgr>();
		// G.C ���� ��꿡�� ���� �ֻ����� ��ġ�Ѵ�. ==> G.C�� ���� ������ ����
		m_This->AddToRoot();

		m_World = _world;
	}

	// ����� ���忡�� ��ü�� ��û�� ���
	if (m_World != _world)
	{
		m_World = _world;
	}

	return m_This;
}

void ULevelStreamMgr::Destroy()
{
	if (nullptr != m_This)
	{
		m_This->ConditionalBeginDestroy();
		m_This = nullptr;
		m_World = nullptr;
	}
}

void ULevelStreamMgr::LoadDataFromFolder(FString _strFolderPath)
{
	UObjectLibrary* ParticleObjLib = UObjectLibrary::CreateLibrary(UParticleSystem::StaticClass(), false, GIsEditor);

	if (nullptr != ParticleObjLib)
	{
		ParticleObjLib->AddToRoot();
		ParticleObjLib->LoadAssetDataFromPath(_strFolderPath);
		ParticleObjLib->GetAssetDataList(m_AssetData);
	}
	UObjectLibrary* SkeletalObjLib = UObjectLibrary::CreateLibrary(USkeletalMesh::StaticClass(), false, GIsEditor);
	if (nullptr != SkeletalObjLib)
	{
		SkeletalObjLib->AddToRoot();
		SkeletalObjLib->LoadAssetDataFromPath(_strFolderPath);
		SkeletalObjLib->GetAssetDataList(m_AssetData);
	}
	UObjectLibrary* ABPObjLib = UObjectLibrary::CreateLibrary(UAnimBlueprint::StaticClass(), false, GIsEditor);
	if (nullptr != ABPObjLib)
	{
		ABPObjLib->AddToRoot();
		ABPObjLib->LoadAssetDataFromPath(_strFolderPath);
		ABPObjLib->GetAssetDataList(m_AssetData);
	}
}

void ULevelStreamMgr::LoadAssetAsync()
{
	// �ε� ��� ����� ������ �����迭
	TArray<FSoftObjectPath> arrPath;

	for (int i = 0; i < m_arrPath.Num(); ++i)
	{
		LOG(Warning, *m_arrPath[i].Name.ToString());
		arrPath.AddUnique(m_arrPath[i].Path);
	}

	// ��Ʈ�� �Ŵ���
	FStreamableManager& streamMgr = UAssetManager::GetStreamableManager();
	m_AssetHandle = streamMgr.RequestAsyncLoad(arrPath, FStreamableDelegate::CreateUObject(this, &ULevelStreamMgr::OnComplete));
}

UObject* ULevelStreamMgr::FindAsset(FName _Name)
{
	UObject* pAsset = m_mapAssets.FindRef(_Name);

	return pAsset;
}

void ULevelStreamMgr::Convert(TArray<FAssetPathInfo>& _arrPathInfo, TArray<UObject*>& _arrAssets)
{
	for (int i = 0; i < _arrPathInfo.Num(); ++i)
	{
		m_mapAssets.Add(_arrPathInfo[i].Name, _arrAssets[i]);
	}
}

void ULevelStreamMgr::OnComplete()
{
	TArray<UObject*> arrAssets;
	m_AssetHandle->GetLoadedAssets(arrAssets);

	Convert(m_arrPath, arrAssets);
}
