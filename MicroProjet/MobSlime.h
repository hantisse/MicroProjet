#pragma once
#include "Mob.h"

class MobSlime : public Mob
{
public:
	MobSlime(tmx::Vector2f position);
	void attack() override;
	void createAttackHitBoxes(b2World& world) override;
	void createBody(b2World& world) override;
	void activeAttackBox(bool active);
private:
	void loadAnimations() override;
	void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);


	b2Fixture* m_attackRangeRight;
	FixtureContactData m_attackRightData;
	b2Fixture* m_attackRangeLeft;
	FixtureContactData m_attackLeftData;
};

