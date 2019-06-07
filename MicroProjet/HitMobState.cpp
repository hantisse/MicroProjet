#include "pch.h"
#include "HitMobState.h"
#include "DeadMobState.h"
#include "SleepingMobState.h"


HitMobState::HitMobState() :
	m_timeOut(0)
{
}

MobStatePtr HitMobState::handlePlayerPos(Mob& mob)
{
	if (mob.dead())
	{
		return 	std::make_unique<DeadMobState>();
	}
	++m_timeOut;
	if (m_timeOut > 1000)
		return 	std::make_unique<SleepingMobState>();
	return NULL;
}

void HitMobState::update(Mob& mob) 
{
	++m_timeOut;
	if (m_timeOut > 1000)
		exit(mob);
};
void HitMobState::enter(Mob& mob)
{
	float impulse = mob.getMass() * -2;
	int dir = mob.getDirection() == RIGHT ? -1 : 1;
	mob.applyLinearImpulseToCenter(b2Vec2(dir * mob.getMass(), impulse), true);
}
void HitMobState::exit(Mob& mob)
{
}
