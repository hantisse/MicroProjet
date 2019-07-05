#include "pch.h"
#include "MobContactAttackBehaviour.h"
#include "Mob.h"
#include <iostream>


MobContactAttackBehaviour::MobContactAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming):
	MobAttackBehaviour(attackDistance, damage, attackRate, attackTiming)
{

}


MobContactAttackBehaviour::~MobContactAttackBehaviour()
{
}


void MobContactAttackBehaviour::activeAttackBox(Mob& mob, bool active)
{
	if (mob.getDirection() == Direction::RIGHT)
	{
		m_attackLeftData.active = false;
		m_attackRightData.active = active;
	}
	else if (mob.getDirection() == Direction::LEFT)
	{
		m_attackLeftData.active = active;
		m_attackRightData.active = false;
	}
}


void MobContactAttackBehaviour::attack(Mob const& mob)
{

	for (b2ContactEdge* ce = mob.getBody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;

		FixtureContactData* contactDataA = static_cast<FixtureContactData*>(c->GetFixtureA()->GetUserData());
		FixtureContactData* contactDataB = static_cast<FixtureContactData*>(c->GetFixtureB()->GetUserData());

		if (contactDataA != nullptr)
		{
			computeAttack(contactDataA, contactDataB);
		}

		if (contactDataB != nullptr)
		{
			computeAttack(contactDataB, contactDataA);
		}
	}
}

void MobContactAttackBehaviour::computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case FIX_MOB_ATTACK:

		if (contactDataB != nullptr)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				Player* player = static_cast<Player*>(contactDataB->origin);
				player->takeDamage(contactDataA->data);
			}
		}
		break;

	default:
		break;
	}
}

void MobContactAttackBehaviour::createAttackHitBoxes(Mob& mob)
{
	b2PolygonShape shape;
	shape.SetAsBox(5, 5, b2Vec2(-10.f, -5), 0);

	b2FixtureDef fixDef;
	fixDef.isSensor = true;
	fixDef.shape = &shape;
	m_attackRangeRight = mob.getBody()->CreateFixture(&fixDef);

	shape.SetAsBox(5, 5, b2Vec2(10.f, -5), 0);
	fixDef.shape = &shape;
	m_attackRangeLeft = mob.getBody()->CreateFixture(&fixDef);

	int attackPower = mob.getModel()->attackPower;
	m_attackRightData = { false, FIX_MOB_ATTACK, attackPower, &mob };
	m_attackLeftData = { false, FIX_MOB_ATTACK, attackPower, &mob };

	m_attackRangeRight->SetUserData(&m_attackRightData);
	m_attackRangeLeft->SetUserData(&m_attackLeftData);
}

void MobContactAttackBehaviour::createBody(Mob& mob)
{
	createAttackHitBoxes(mob);
}