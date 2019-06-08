#include "pch.h"
#include <iostream>
#include "AttackingMobState.h"
#include "SleepingMobState.h"
#include "DeadMobState.h"


AttackingMobState::AttackingMobState() :
	m_attackTimeOut(0)
{
}

MobStatePtr AttackingMobState::handlePlayerPos(Mob& mob)
{
	if (!mob.canAttack())
	{
		exit(mob);
		return std::make_unique<SleepingMobState>();
	}

	return NULL;
}


void AttackingMobState::update(Mob& mob)
{
	++m_attackTimeOut;

	
	if (!mob.isAnimationPlaying())
	{

		if (m_attackTimeOut > mob.getAttackRate())
		{
			//mob.attack();
			mob.playAnimation("attack");
			m_attackTimeOut = 0;

		}
		else
		{
			//mob.activeAttackBox(false);
			mob.playAnimation("idle");
		}
	}

	if (m_attackTimeOut == mob.getAttackTiming())
	{
		mob.attack();
	}


}

void AttackingMobState::enter(Mob& mob)
{
	mob.activeAttackBox(true);
	mob.playAnimation("attack");
}

void AttackingMobState::exit(Mob& mob) 
{
	mob.activeAttackBox(true);

}

