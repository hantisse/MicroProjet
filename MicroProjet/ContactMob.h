#pragma once
#include "Mob.h"

class ContactMob : public Mob
{
public:
	ContactMob(EntityID id, int activationDistance, tmx::Vector2f position);
	~ContactMob();

	virtual void attack() override;
	virtual void createAttackHitBoxes(b2World& world);
	virtual void activeAttackBox(bool active) override;
	virtual void createBody(b2World& world) override;
protected:
	virtual void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);


	b2Fixture* m_attackRangeRight;
	FixtureContactData m_attackRightData;
	b2Fixture* m_attackRangeLeft;
	FixtureContactData m_attackLeftData;
};

