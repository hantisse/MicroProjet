#include "pch.h"
#include "Player.h"
#include <iostream>
#include "StandingPlayerState.h"


Player::Player()
{
	m_bodyDef.position.Set(100, 0);
	m_bodyDef.type = b2_dynamicBody;

	m_bodyShape.SetAsBox(10.f/30, 10.f/30);
	 
	m_bodyFixDef.shape = &m_bodyShape;
	m_bodyFixDef.density = 1.0f;
	m_bodyFixDef.friction = 0.3f;


	m_footShape.SetAsBox(5/30, 5/30, b2Vec2(0, 5), 0);
	m_footSensorFixDef.isSensor = true;
	m_footSensorFixDef.shape = &m_footShape;
		
	
	m_sfShape = sf::RectangleShape(sf::Vector2f(10, 10));
	m_sfShape.setOrigin(5, 5);
	m_sfShape.setFillColor(sf::Color::Magenta);


	m_states.push(std::make_unique<StandingPlayerState>());

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
	target.draw(m_sfShape);
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

StatePtr Player::endState() 
{
	m_states.pop();
	return std::move(m_states.top());
}

