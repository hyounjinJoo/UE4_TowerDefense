#pragma once

#include "../global.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EffectMgr.generated.h"

UCLASS()
class TOWERDEFENSE_API UEffectMgr : public UObject
{
	GENERATED_BODY()
private:
	static UEffectMgr*	m_This;
	static UWorld*		m_World;

public:
	static UEffectMgr* GetInst(UWorld* _world);
	static void Destroy();


public:
	void CreateEffect(EEFFECT_TYPE _type, FTransform _trans, ULevel* _Level);

private:
	UEffectMgr();
	~UEffectMgr();
};
