#include "MonsterAnimInstance.h"

#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
	: m_eState(EMON_STATE::IDLE)
{

}

// 객체 생성 시
void UMonsterAnimInstance::NativeInitializeAnimation()
{
	
}

// 게임 시작 시
void UMonsterAnimInstance::NativeBeginPlay()
{
}

// 게임 시작 후 매 프레임마다 호출
void UMonsterAnimInstance::NativeUpdateAnimation(float _fDT)
{
	AMonster* pMonster = Cast<AMonster>(GetOwningActor());

	if (nullptr != pMonster)
	{
		m_eState = pMonster->GetState();
	}
	
}

void UMonsterAnimInstance::AnimNotify_NormalMon_HitEnd()
{
	AMonster* pMonster = Cast<AMonster>(GetOwningActor());

	if (nullptr != pMonster)
	{
		// 히트 모션에 의한 경직을 풀어 줌
		pMonster->SetUnStopable(false);
		pMonster->ChangeState(EMON_STATE::MOVE);
	}
}
