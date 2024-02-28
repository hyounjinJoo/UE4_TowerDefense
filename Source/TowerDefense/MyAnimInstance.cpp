#include "MyAnimInstance.h"

#include "Tower/MyTower.h"

UMyAnimInstance::UMyAnimInstance()
	: m_eState(ETOWER_STATE::INSTALL)
{

}

void UMyAnimInstance::NativeInitializeAnimation()
{
}

void UMyAnimInstance::NativeBeginPlay()
{
}

void UMyAnimInstance::NativeUpdateAnimation(float _fDT)
{
	AMyTower* pTower = Cast<AMyTower>(GetOwningActor());

	if (nullptr != pTower)
	{
		m_fDirection = pTower->GetDirection();
		m_eState = pTower->GetState();
		m_fAttackSpeed = pTower->GetAttackSpeed();
	}
}

void UMyAnimInstance::AnimNotify_AttackEnd()
{
	AMyTower* pTower = Cast<AMyTower>(GetOwningActor());

	if (nullptr != pTower)
	{
		pTower->ChangeState(ETOWER_STATE::IDLE);
	}
}

void UMyAnimInstance::AnimNotify_Fire()
{
	AMyTower* pTower = Cast<AMyTower>(GetOwningActor());

	if (nullptr != pTower)
	{
		pTower->Fire();
	}

}

void UMyAnimInstance::AnimNotify_InstallEnd()
{
	AMyTower* pTower = Cast<AMyTower>(GetOwningActor());
	if (nullptr != pTower)
	{
		pTower->ChangeState(ETOWER_STATE::IDLE);
	}

}

void UMyAnimInstance::AnimNotify_RemoveEnd()
{
	AMyTower* pTower = Cast<AMyTower>(GetOwningActor());

	if (nullptr != pTower)
	{
		if (ETOWER_STATE::REMOVE == pTower->GetState())
		{
			pTower->DestroyProcess();
		}
		if(ETOWER_STATE::REMOVEWITHUPGRADE == pTower->GetState())
		{
			pTower->ChangeState(ETOWER_STATE::NEEDUPGRADE);
		}
	}
}
