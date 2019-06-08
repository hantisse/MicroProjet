#include "pch.h"
#include "MobFireElemental.h"
#include "SleepingMobState.h"
#include <iostream>
#include "Projectile.h"

MobFireElemental::MobFireElemental(tmx::Vector2f position) :
	DistanceMob(EntityID::FIRE_ELEMENTAL, 150, position)
{

	m_maxHealth = 20;
	m_health = m_maxHealth;
	m_attackPower = 10;
	m_attackRate = 3000;
	m_attackTiming = 0;

	m_bodyDef.type = b2_dynamicBody;
	
	m_sprite.setOrigin(16, 28);

	loadAnimations();

	m_state = std::make_unique<SleepingMobState>();
}

void MobFireElemental::loadAnimations()
{
	thor::FrameAnimation idle, attack, die;

	idle.addFrame(1.f, sf::IntRect(0, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(32, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(64, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(96, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(128, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(160, 32, 32, 32));


	attack.addFrame(1.f, sf::IntRect(0, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(32, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(64, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(96, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(128, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(160, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(192, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(224, 64, 32, 32));

	die.addFrame(1.f, sf::IntRect(0, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(32, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(64, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(96, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(128, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(160, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(192, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(224, 128, 32, 32));

	m_animator.addAnimation("idle", idle, sf::seconds(.5f));
	m_animator.addAnimation("attack", attack, sf::seconds(.3f));
	m_animator.addAnimation("die", die, sf::seconds(.3f));
}


void MobFireElemental::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Mob::draw(target, states);
	for (auto const& proj : m_projectiles)
	{
		//std::cout << proj->m_sprite.getLocalBounds().width << " " << proj->m_sprite.getGlobalBounds().height << std::endl;
		proj->draw(target, states);
	}
}
