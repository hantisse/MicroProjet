#include "pch.h"
#include "Player.h"
#include "Mob.h"
#include <iostream>
#include "StandingPlayerState.h"
#include "DeadPlayerState.h"


Player::Player() :
	LivingEntity(EntityID::PLAYER)
{

	m_activationFlags = 0x0000;

	m_bodyDef.position.Set(100, 200);
	m_bodyDef.type = b2_dynamicBody;

	
	m_bodyData = { true, FIX_PLAYER, getModel()->attackPower, this };

	m_footShape.SetAsBox(2.5, 2.5, b2Vec2(0, 10), 0);
	m_footSensorFixDef.isSensor = true;
	m_footSensorFixDef.shape = &m_footShape;
	
	
	m_sprite.setOrigin(25, 28);

	loadAnimations();

	m_states.push(std::make_unique<StandingPlayerState>());

}

void Player::loadAnimations()
{
	thor::FrameAnimation idle, jump, run, fall, attack, block;

	idle.addFrame(1.f, sf::IntRect(0, 0, 50, 36));
	idle.addFrame(1.f, sf::IntRect(50, 0, 50, 36));
	idle.addFrame(1.f, sf::IntRect(100, 0, 50, 36));
	idle.addFrame(1.f, sf::IntRect(150, 0, 50, 36));

	
	run.addFrame(1.f, sf::IntRect(50, 36, 50, 37));
	run.addFrame(1.f, sf::IntRect(100, 36, 50, 37));


	jump.addFrame(1.f, sf::IntRect(100, 73, 50, 37));
	jump.addFrame(1.f, sf::IntRect(150, 73, 50, 37));
	jump.addFrame(1.f, sf::IntRect(200, 73, 50, 37));
	jump.addFrame(1.f, sf::IntRect(250, 73, 50, 37));
	jump.addFrame(1.f, sf::IntRect(300, 73, 50, 37));
	jump.addFrame(1.f, sf::IntRect(0, 110, 50, 37));
	jump.addFrame(1.f, sf::IntRect(50, 110, 50, 37));


	fall.addFrame(1.f, sf::IntRect(50, 110, 50, 37));

	attack.addFrame(1.f, sf::IntRect(0, 258, 50, 37));
	attack.addFrame(1.f, sf::IntRect(50, 258, 50, 37));
	attack.addFrame(1.f, sf::IntRect(100, 258, 50, 37));
	attack.addFrame(1.f, sf::IntRect(150, 258, 50, 37));
	
	block.addFrame(1.f, sf::IntRect(200, 221, 50, 37));
	block.addFrame(1.f, sf::IntRect(150, 221, 50, 37));
	block.addFrame(1.f, sf::IntRect(100, 221, 50, 37));
	
	m_animator.addAnimation("idle", idle, sf::seconds(1.f));
	m_animator.addAnimation("jump", jump, sf::seconds(.25f));
	m_animator.addAnimation("run", run, sf::seconds(.3f));
	m_animator.addAnimation("fall", fall, sf::seconds(.3f));
	m_animator.addAnimation("attack", attack, sf::seconds(.3f));
	m_animator.addAnimation("block", block, sf::seconds(.1f));
	m_animator.addAnimation("die", idle, sf::seconds(.1f));

}

void Player::update(sf::Time dt) 
{
	Entity::update(dt);
	m_states.top()->update(*this);
	m_lifeBar.setPosition(m_body->GetPosition().x, m_body->GetPosition().y - 30);
	m_life.setScale(std::max(0., static_cast<double>(m_health) / getModel()->maxHealth), 1);
	m_life.setPosition(m_body->GetPosition().x - m_lifeBar.getGlobalBounds().width / 2, m_body->GetPosition().y - 30);
}

void Player::createBody(b2World& world)
{
	Entity::createBody(world);
	m_body->SetFixedRotation(true);

	m_footData = { true, FIX_FOOT, m_nbFootContacts, this };
	m_footSensorFixDef.userData = &m_footData;
	m_body->CreateFixture(&m_footSensorFixDef);

	

	createWeaponHitBoxes(world);

	
}

void Player::createWeaponHitBoxes(b2World& world)
{
	b2PolygonShape shape;
	shape.SetAsBox(6, 6, b2Vec2(-15.f, -5), 0);

	b2FixtureDef fixDef;
	fixDef.isSensor = true;

	fixDef.shape = &shape;
	fixDef.filter.categoryBits = FIX_SWORD;
	m_swordFixLeft = m_body->CreateFixture(&fixDef);

	shape.SetAsBox(6, 6, b2Vec2(15.f, -5), 0);
	fixDef.shape = &shape;
	m_swordFixRight = m_body->CreateFixture(&fixDef);

	int attackPower = getModel()->attackPower;
	m_swordLeftData = { false, FIX_SWORD, attackPower, this };
	m_swordRightData = { false, FIX_SWORD, attackPower, this };

	m_swordFixRight->SetUserData(&m_swordRightData);
	m_swordFixLeft->SetUserData(&m_swordLeftData);

	fixDef.filter.categoryBits = FIX_SHIELD;

	shape.SetAsBox(6, 8, b2Vec2(-15.f, -5), 0);
	fixDef.shape = &shape;
	m_shieldFixLeft = m_body->CreateFixture(&fixDef);

	shape.SetAsBox(6, 8, b2Vec2(15.f, -5), 0);
	fixDef.shape = &shape;
	m_shieldFixRight = m_body->CreateFixture(&fixDef);

	m_shieldLeftData = { false, FIX_SHIELD, 0, this };
	m_shieldRightData = { false, FIX_SHIELD, 0, this };

	m_shieldFixRight->SetUserData(&m_shieldRightData);
	m_shieldFixLeft->SetUserData(&m_shieldLeftData);


}



void Player::handleInput(sf::Event& sfEvent)
{
	StatePtr newState = !m_states.empty() ? m_states.top()->handleInput(*this, sfEvent): std::make_unique<StandingPlayerState>();
	if (newState != NULL)
	{
		m_states.push(std::move(newState));
		m_states.top()->enter(*this);
	}

}

void Player::activeSword(bool active)
{
	if (m_direction == Direction::RIGHT)
	{
		m_swordLeftData.active = false;
		m_swordRightData.active = active;
	} 
	else if (m_direction == Direction::LEFT)
	{
		m_swordLeftData.active = active;
		m_swordRightData.active = false;
	}
}


void Player::activeShield(bool active)
{
	if (m_direction == Direction::RIGHT)
	{
		m_shieldLeftData.active = false;
		m_shieldRightData.active = active;
	}
	else if (m_direction == Direction::LEFT)
	{
		m_shieldLeftData.active = active;
		m_shieldRightData.active = false;
	}
}

void Player::attack()
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


void Player::computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case FIX_SWORD:

		if (contactDataB != nullptr && contactDataA->active)
		{

			if (contactDataB->type == FIX_MOB)
			{

				
				Mob* mob = static_cast<Mob*>(contactDataB->origin);
				mob->takeDamage(getModel()->attackPower);
				
			}
		}
		break;
	
	default:
		break;
	}
}

void Player::addActivation(unsigned short const flag)
{
	m_activationFlags |= flag;
}

unsigned short Player::getActivationFlags() const
{
	return m_activationFlags;
}

void Player::endState() 
{
	m_states.pop();
	m_states.top()->enter(*this);
}


void Player::kill()
{
	
}
void Player::takeDamage(int damage)
{
	m_health -= damage;
	if (dead())
	{
		m_states.push(std::make_unique<DeadPlayerState>());
		m_states.top()->enter(*this);
	}
	
}
void Player::setImmune(bool b)
{

}
