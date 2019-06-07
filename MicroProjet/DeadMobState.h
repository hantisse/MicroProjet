#pragma once
#include "MobState.h"

class DeadMobState : public MobState
{
public:
	DeadMobState() = default;

	MobStatePtr handlePlayerPos(Mob& mob) override;

	void update(Mob& mob) override;
	void enter(Mob& mob) override;
	void exit(Mob& mob) override;
};

