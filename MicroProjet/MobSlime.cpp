#include "pch.h"
#include "MobSlime.h"
#include "SleepingMobState.h"
#include <iostream>
#include "Player.h"


MobSlime::MobSlime(tmx::Vector2f position) :
	Mob("Assets/images/mobs/slime.png", 40, position)
{

	m_maxHealth = 20;
	m_health = m_maxHealth;
	m_attackPower = 10;
	m_attackRate = 3000;

	m_bodyDef.type = b2_dynamicBody;

	m_bodyShape.SetAsBox(8.f, 6.f);

	m_bodyFixDef.shape = &m_bodyShape;
	m_bodyFixDef.density = 15.f;
	m_bodyFixDef.filter.categoryBits = FixtureType::MOB;

	
	m_spriteRect = sf::IntRect(0, 0, 32, 32);

	m_sprite = sf::Sprite(m_sourceTexture, m_spriteRect);
	m_sprite.setOrigin(16, 20);

	loadAnimations();

	m_state = std::make_unique<SleepingMobState>();
}

void MobSlime::loadAnimations()
{
	thor::FrameAnimation idle, attack, die;

	idle.addFrame(1.f, sf::IntRect(224, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(192, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(160, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(128, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(96, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(64, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(32, 0, 32, 24));
	idle.addFrame(1.f, sf::IntRect(0, 0, 32, 24));


	attack.addFrame(1.f, sf::IntRect(224, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(192, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(160, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(128, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(96, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(64, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(32, 24, 32, 25));
	attack.addFrame(1.f, sf::IntRect(0, 24, 32, 25));

	die.addFrame(1.f, sf::IntRect(224, 49, 32, 25));
	die.addFrame(1.f, sf::IntRect(192, 49, 32, 25));
	die.addFrame(1.f, sf::IntRect(160, 49, 32, 25));
	die.addFrame(1.f, sf::IntRect(96, 49, 32, 25));
	die.addFrame(1.f, sf::IntRect(64, 49, 32, 25));

	m_animator.addAnimation("idle", idle, sf::seconds(.8f));
	m_animator.addAnimation("attack", attack, sf::seconds(.8f));
	m_animator.addAnimation("die", die, sf::seconds(.5f));
}


void MobSlime::createBody(b2World& world)
{
	Entity::createBody(world);
	createAttackHitBoxes(world);

}

void MobSlime::activeAttackBox(bool active)
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

void MobSlime::attack()
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



void MobSlime::computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case MOB_ATTACK:

		if (contactDataB != nullptr && contactDataA->active)
		{

			if (contactDataB->type = FixtureType::PLAYER)
			{
				*(contactDataB->data) -= *(contactDataA->data);
				Player* player = static_cast<Player*>(contactDataB->origin);
				//player->hitByMob();
				std::cout << "Slime attack : " << *(contactDataB->data);

			}
		}
		break;

	default:
		break;
	}
}

void MobSlime::createAttackHitBoxes(b2World& world)
{
	b2PolygonShape shape;
	shape.SetAsBox(3, 4, b2Vec2(-10.f, -5), 0);

	b2FixtureDef fixDef;
	fixDef.isSensor = true;
	fixDef.shape = &shape;
	m_attackRangeRight = m_body->CreateFixture(&fixDef);

	shape.SetAsBox(3, 4, b2Vec2(10.f, -5), 0);
	fixDef.shape = &shape;
	m_attackRangeLeft = m_body->CreateFixture(&fixDef);

	m_attackRightData = { false, FixtureType::MOB_ATTACK, &m_attackPower, this };
	m_attackLeftData = { false, FixtureType::MOB_ATTACK, &m_attackPower, this };

	m_attackRangeRight->SetUserData(&m_attackRightData);
	m_attackRangeLeft->SetUserData(&m_attackLeftData);
}
