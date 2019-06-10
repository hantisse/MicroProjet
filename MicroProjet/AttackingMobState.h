#pragma once
#include "MobState.h"

//State of attacking Mobs
class AttackingMobState : public MobState
{
public:
	AttackingMobState();
	virtual MobStatePtr handlePlayerPos(Mob& mob);

	virtual void update(Mob& mob) override;
	virtual void enter(Mob& mob) override;
	virtual void exit(Mob& mob) override;

private:
	//Time between two attacks
	int m_attackTimeOut;
	
};

