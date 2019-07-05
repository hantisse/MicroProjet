#pragma once
#include "Mob.h"


class MobState
{
public:


	MobState() = default;

	//To change state depending on the player position
	virtual MobStatePtr handlePlayerPos(Mob& mob) = 0;

	//called after handlePlayerPos
	virtual void update(Mob& mob);
	virtual void enter(Mob& mob) = 0;
	virtual void exit(Mob& mob);

};

