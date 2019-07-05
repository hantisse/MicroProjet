#pragma once
#include "MobAttackBehaviour.h"

class MobContactAttackBehaviour : public MobAttackBehaviour
{
public:
	MobContactAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming);
	~MobContactAttackBehaviour();

	void attack(Mob const& mob) override;
	void activeAttackBox(Mob& mob, bool active) override;
	void createBody(Mob& mob) override;


private:
	void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);
	void createAttackHitBoxes(Mob& mob);

	//Sensor for right attack
	b2Fixture* m_attackRangeRight;
	FixtureContactData m_attackRightData;
	//Sensor for left attack
	b2Fixture* m_attackRangeLeft;
	FixtureContactData m_attackLeftData;

};

