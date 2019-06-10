#pragma once
#include "MobState.h"

//State after a mob was hit by the player
class HitMobState : public MobState
{
public:
	HitMobState();

	MobStatePtr handlePlayerPos(Mob& mob) override;


	void update(Mob& mob) override;
	void enter(Mob& mob) override;
	void exit(Mob& mob) override;
private:
	int m_timeOut;

};

