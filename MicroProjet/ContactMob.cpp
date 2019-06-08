#include "pch.h"
#include "ContactMob.h"
#include "MobState.h"


ContactMob::ContactMob(EntityID id, int activationDistance, tmx::Vector2f position) :
	Mob(id, activationDistance, position)
{
}


void ContactMob::activeAttackBox(bool active)
{
	if (m_direction == Direction::RIGHT)
	{
		m_attackLeftData.active = false;
		m_attackRightData.active = active;
	}
	else if (m_direction == Direction::LEFT)
	{
		m_attackLeftData.active = active;
		m_attackRightData.active = false;
	}
}


void ContactMob::attack()
{
	for (b2ContactEdge* ce = m_body->GetContactList(); ce; ce = ce->next)
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


void ContactMob::computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case FIX_MOB_ATTACK:

		if (contactDataB != nullptr)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				*(contactDataB->data) -= *(contactDataA->data);
			}
		}
		break;

	default:
		break;
	}
}

void ContactMob::createBody(b2World& world)
{
	Entity::createBody(world);
	createAttackHitBoxes(world);

}

void ContactMob::createAttackHitBoxes(b2World& world)
{
	b2PolygonShape shape;
	shape.SetAsBox(5, 5, b2Vec2(-10.f, -5), 0);

	b2FixtureDef fixDef;
	fixDef.isSensor = true;
	fixDef.shape = &shape;
	m_attackRangeRight = m_body->CreateFixture(&fixDef);

	shape.SetAsBox(5, 5, b2Vec2(10.f, -5), 0);
	fixDef.shape = &shape;
	m_attackRangeLeft = m_body->CreateFixture(&fixDef);

	m_attackRightData = { false, FIX_MOB_ATTACK, &m_attackPower, this };
	m_attackLeftData = { false, FIX_MOB_ATTACK, &m_attackPower, this };

	m_attackRangeRight->SetUserData(&m_attackRightData);
	m_attackRangeLeft->SetUserData(&m_attackLeftData);
}


ContactMob::~ContactMob()
{
}
