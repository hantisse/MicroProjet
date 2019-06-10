#pragma once
#include "Mob.h"

//Melee Mob
class ContactMob : public Mob
{
public:
	ContactMob(EntityID id, tmx::Vector2f position);
	~ContactMob();

	virtual void attack() override;

	virtual void activeAttackBox(bool active) override;
	virtual void createBody(b2World& world) override;
protected:
	//Called in createBody function. Needs to be called after the body is created.
	virtual void createAttackHitBoxes(b2World& world);
	
	//Called in attack function, applies damage if needed
	virtual void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);

	//Sensor for right attack
	b2Fixture* m_attackRangeRight;
	FixtureContactData m_attackRightData;
	//Sensor for left attack
	b2Fixture* m_attackRangeLeft;
	FixtureContactData m_attackLeftData;
};

