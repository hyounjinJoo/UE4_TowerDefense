// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectMgr.h"

#include "../Effect/MyEffect.h"

UEffectMgr* UEffectMgr::m_This = nullptr;
UWorld* UEffectMgr::m_World = nullptr;

UEffectMgr::UEffectMgr()
{
}

UEffectMgr::~UEffectMgr()
{
}

UEffectMgr* UEffectMgr::GetInst(UWorld* _world)
{
	if (nullptr == m_This)
	{
		// ���� �ش�.
		// ������ ȣ�� �� HeapMemory�� NewObject�� ��ӹ��� UEffectMgr ��ü 1���� �����Ѵ�.
		// ���ÿ� NewObject�� ��ӹ������ν� G.C�� ����� �ȴ�.
		m_This = NewObject<UEffectMgr>();
		// G.C ���� ��꿡�� ���� �ֻ����� ��ġ�Ѵ�. ==> G.C�� ���� ������ ����
		m_This->AddToRoot();

		m_World = _world;
	}

	// ����� ���忡�� ��ü�� ��û�� ���
	if (m_World != _world)
	{
		m_World = _world;
	}

	//UWorld* pWorld = nullptr;
	//// ���� �����͸� ���� ����־� �޾ƿ;� �Ѵ�.
	//UGameInstance* pInst = UGameplayStatics::GetGameInstance(pWorld)
	//pInst->GetEngine()->OnWorldDestroyed().AddStatic();

	return m_This;
}

void UEffectMgr::Destroy()
{
	if (nullptr != m_This)
	{
		m_This->ConditionalBeginDestroy();
		m_This = nullptr;
		m_World = nullptr;
	}
}

void UEffectMgr::CreateEffect(EEFFECT_TYPE _type, FTransform _trans, ULevel* _Level)
{
	FActorSpawnParameters SpawnParam = {};

	// ���� ����
	SpawnParam.OverrideLevel = _Level;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	AMyEffect* pEffect = m_World->SpawnActor<AMyEffect>(AMyEffect::StaticClass(), _trans, SpawnParam);
	
	pEffect->SetEffectType(_type);

	pEffect->FinishSpawning(pEffect->GetTransform());
}