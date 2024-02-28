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
		// 만들어서 준다.
		// 생성자 호출 및 HeapMemory에 NewObject를 상속받은 UEffectMgr 객체 1개를 생성한다.
		// 동시에 NewObject를 상속받음으로써 G.C에 등록이 된다.
		m_This = NewObject<UEffectMgr>();
		// G.C 참조 계산에서 가장 최상위에 위치한다. ==> G.C에 의한 삭제를 방지
		m_This->AddToRoot();

		m_World = _world;
	}

	// 변경된 월드에서 객체를 요청한 경우
	if (m_World != _world)
	{
		m_World = _world;
	}

	//UWorld* pWorld = nullptr;
	//// 월드 포인터를 같이 집어넣어 받아와야 한다.
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

	// 지연 생성
	SpawnParam.OverrideLevel = _Level;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParam.bDeferConstruction = true;

	AMyEffect* pEffect = m_World->SpawnActor<AMyEffect>(AMyEffect::StaticClass(), _trans, SpawnParam);
	
	pEffect->SetEffectType(_type);

	pEffect->FinishSpawning(pEffect->GetTransform());
}