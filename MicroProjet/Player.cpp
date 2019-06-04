#include "pch.h"
#include "Player.h"
#include <iostream>
#include "StandingPlayerState.h"


Player::Player()
{
	m_bodyDef.position.Set(100, 0);
	m_bodyDef.type = b2_dynamicBody;

	m_bodyShape.SetAsBox(5.f, 10.f);
	 
	m_bodyFixDef.shape = &m_bodyShape;
	m_bodyFixDef.density = 1.0f;
	m_bodyFixDef.friction = 0.3f;


	m_footShape.SetAsBox(2.5, 2.5, b2Vec2(0, 10), 0);
	m_footSensorFixDef.isSensor = true;
	m_footSensorFixDef.shape = &m_footShape;
		
	
	m_sourceTexture.loadFromFile("Assets/images/player/adventurer.png");
	if (!m_sourceTexture.loadFromFile("image.png"))
	{
		std::cout << "Sprite could not be loaded" << std::endl;
	}
	m_spriteRect = sf::IntRect(0, 0, 50, 36);

	m_sprite = sf::Sprite(m_sourceTexture, m_spriteRect);
	m_sprite.setOrigin(25, 28);

	loadAnimations();

	m_states.push(std::make_unique<StandingPlayerState>());

}

void Player::loadAnimations()
{
	thor::FrameAnimation idle, jump, run;

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
	jump.addFrame(1.f, sf::IntRect(0, 110, 50, 37));
	jump.addFrame(1.f, sf::IntRect(50, 110, 50, 37));

	
	m_animator.addAnimation("idle", idle, sf::seconds(1.f));
	m_animator.addAnimation("jump", jump, sf::seconds(.3f));
	m_animator.addAnimation("run", run, sf::seconds(.3f));

}

void Player::update(sf::Time dt) 
{
	Entity::update(dt);
	m_states.top()->update(*this);
}

void Player::createBody(b2World& world)
{
	Entity::createBody(world);
	m_body->SetFixedRotation(true);
	m_footSensorFixDef.userData = (void*)3;
	b2Fixture* fixture = m_body->CreateFixture(&m_footSensorFixDef);

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//target.draw(m_sfShape);
	target.draw(m_sprite);
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

void Player::endState() 
{
	m_states.pop();
	m_states.top()->enter(*this);
}

