#pragma once
#include "MobState.h"

class AttackingMobState : public MobState
{
public:
	AttackingMobState();

	virtual MobStatePtr handlePlayerPos(Mob& mob);

	virtual void update(Mob& mob) override;
	virtual void enter(Mob& mob) override;
	virtual void exit(Mob& mob) override;

private:
	int m_attackTimeOut;
	
};

