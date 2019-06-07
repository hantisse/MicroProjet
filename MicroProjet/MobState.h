#pragma once
#include "Mob.h"

class Mob;

class MobState
{
public:
	MobState() = default;

	virtual MobStatePtr handlePlayerPos(Mob& mob) = 0;

	virtual void update(Mob& mob) {};
	virtual void enter(Mob& mob) = 0;
	virtual void exit(Mob& mob) {};

};

