#pragma once
#include "MobState.h"


class SeekingMobState : public MobState
{
public:
	SeekingMobState();
	virtual MobStatePtr handlePlayerPos(Mob& mob) override;

	virtual void update(Mob& mob) override;
	virtual void enter(Mob& mob) override;
	virtual void exit(Mob& mob) override;
};

