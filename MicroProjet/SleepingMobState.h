#pragma once
#include "MobState.h"

class Mob;

class SleepingMobState : public MobState
{
public:
	SleepingMobState();
	virtual MobStatePtr handlePlayerPos(Mob& mob) override;

	virtual void update(Mob& mob) override;
	virtual void enter(Mob& mob) override;
	virtual void exit(Mob& mob) override;
};

