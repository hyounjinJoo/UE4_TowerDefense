#include "MonsterAnimInstance.h"

#include "Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
	: m_eState(EMON_STATE::IDLE)
{

}

// ��ü ���� ��
void UMonsterAnimInstance::NativeInitializeAnimation()
{
	
}

// ���� ���� ��
void UMonsterAnimInstance::NativeBeginPlay()
{
}

// ���� ���� �� �� �����Ӹ��� ȣ��
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
		// ��Ʈ ��ǿ� ���� ������ Ǯ�� ��
		pMonster->SetUnStopable(false);
		pMonster->ChangeState(EMON_STATE::MOVE);
	}
}
