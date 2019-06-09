#include "pch.h"
#include "MobSlime.h"
#include "SleepingMobState.h"
#include <iostream>
#include "Player.h"


MobSlime::MobSlime(tmx::Vector2f position) :
	ContactMob(EntityID::SLIME, position)
{
	/*
	m_wakeDistance = 150;
	m_maxHealth = 20;

	m_attackPower = 10;
	m_attackRate = 3000;
	m_attackTiming = 700;
	m_maxVel = 1;
	*/
	m_bodyDef.type = b2_dynamicBody;
	
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

