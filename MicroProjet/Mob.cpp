#include "pch.h"
#include "Mob.h"
#include <iostream>
#include "AttackingMobState.h"
#include "SleepingMobState.h"
#include "DeadMobState.h"
#include "HitMobState.h"

Mob::Mob(std::string texturePath, int activationDistance, tmx::Vector2f position) :
	LivingEntity(texturePath),
	m_attackDist(activationDistance),
	m_distanceToPlayer(100)
	
{
	m_bodyDef.position.Set(position.x, position.y);
	m_bodyData = { true, FixtureType::MOB, &m_health, this };
	m_bodyFixDef.userData = &m_bodyData;

	m_lifeBar.setFillColor(sf::Color::Red);
	m_lifeBar.setOrigin(20, 0);
	m_life.setFillColor(sf::Color::Green);

}

void Mob::update(sf::Time dt)
{

	if (m_distanceToPlayer > 400)
		return;
	Entity::update(dt);
	handlePlayerPos();
	m_state->update(*this);
	m_lifeBar.setPosition(m_body->GetPosition().x, m_body->GetPosition().y - 20);
	m_life.setScale(std::max(0.,static_cast<double>(m_health) / m_maxHealth), 1);
	m_life.setPosition(m_body->GetPosition().x - m_lifeBar.getGlobalBounds().width/2, m_body->GetPosition().y - 20);
}

void Mob::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_distanceToPlayer > 400)
		return;
	LivingEntity::draw(target, states);
}


void Mob::handlePlayerPos()
{
	MobStatePtr newState = m_state->handlePlayerPos(*this);
	if (newState != NULL)
	{
		m_state = std::move(newState);
		m_state->enter(*this);
	}
}



void Mob::hitByPlayer()
{
	m_state = std::make_unique<HitMobState>();
	m_state->enter(*this);
	
}

void Mob::updateDistToPlayer(sf::Vector2f playerPos)
{
	m_distanceToPlayer = std::sqrt((std::pow(m_body->GetPosition().x - playerPos.x, 2) + std::pow(m_body->GetPosition().y - playerPos.y, 2)));
	setDirection((m_body->GetPosition().x - playerPos.x) < 0 ? Direction::RIGHT : Direction::LEFT);

}
