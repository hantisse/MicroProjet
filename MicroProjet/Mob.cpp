#include "pch.h"
#include "Mob.h"
#include <iostream>
#include "HitMobState.h"

Mob::Mob(EntityID id, tmx::Vector2f position) :
	LivingEntity(id)
	
{
	m_bodyDef.position.Set(position.x, position.y);
	m_bodyData = { true, FIX_MOB, getModel()->attackPower, this };
	
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
	m_life.setScale(std::max(0.,static_cast<double>(m_health) / getModel()->maxHealth), 1);
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



void Mob::hitByPlayer(int damage)
{
	m_health -= damage;
	m_state = std::make_unique<HitMobState>();
	m_state->enter(*this);
	
}

void Mob::updateDistToPlayer(sf::Vector2f playerPos)
{

	m_distanceToPlayer = std::sqrt((std::pow(m_body->GetPosition().x - playerPos.x, 2) + std::pow(m_body->GetPosition().y - playerPos.y, 2)));
	setDirection((m_body->GetPosition().x - playerPos.x) < 0 ? Direction::RIGHT : Direction::LEFT);

}

bool Mob::canAttack() 
{ 
	return m_distanceToPlayer < getModel()->attackDist; 
}

bool Mob::canMove() 
{ 
	return getModel()->canMove; 
}
bool Mob::awake() { 
	return m_distanceToPlayer < getModel()->wakeDistance; 
}
int Mob::getAttackRate() 
{
	return getModel()->attackRate; 
}
int Mob::getAttackTiming() 
{ 
	return getModel()->attackTiming; 
}

MobModel const* Mob::getModel()
{
	assert(m_model->type == MOD_MOB);
	return static_cast<MobModel*>(m_model.get());
}