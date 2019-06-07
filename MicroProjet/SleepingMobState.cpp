#include "pch.h"
#include <iostream>
#include "SleepingMobState.h"
#include "AttackingMobState.h"
#include "DeadMobState.h"


SleepingMobState::SleepingMobState()
{
}

MobStatePtr SleepingMobState::handlePlayerPos(Mob& mob)
{

	if (mob.canAttack())
	{
		return std::make_unique<AttackingMobState>();
	}

	return NULL;
}


void SleepingMobState::update(Mob& mob)
{
	
	if (!mob.isAnimationPlaying())
	{
		mob.playAnimation("idle");
	}

}

void SleepingMobState::enter(Mob& mob)
{

}

void SleepingMobState::exit(Mob& mob)
{

}


