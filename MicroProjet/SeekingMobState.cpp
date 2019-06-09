#include "pch.h"
#include "SeekingMobState.h"
#include "AttackingMobState.h"
#include "SleepingMobState.h"
#include <iostream>

SeekingMobState::SeekingMobState()
{
}

MobStatePtr SeekingMobState::handlePlayerPos(Mob& mob)
{
	if (mob.canAttack())
	{
		exit(mob);
		return std::make_unique<AttackingMobState>();
	}

	if (!mob.awake())
	{
		exit(mob);
		return std::make_unique<SleepingMobState>();
	}

}

void SeekingMobState::update(Mob& mob)
{
	if (mob.canMove())
	{
		int mult = mob.getDirection() == RIGHT ? 1 : -1;
		mob.setLinearVelocity(b2Vec2(mult*mob.getMaxVel(), mob.getLinearVelocity().y));
	}

	if (!mob.isAnimationPlaying())
	{
		mob.playAnimation("idle");
	}


}
void SeekingMobState::enter(Mob& mob)
{
	std::cout << "seeking" << std::endl;
}

void SeekingMobState::exit(Mob& mob)
{

}