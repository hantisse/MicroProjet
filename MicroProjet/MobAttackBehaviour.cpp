#include "pch.h"
#include "MobAttackBehaviour.h"
#include "Mob.h"

MobAttackBehaviour::MobAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming) :
	m_attackDistance(attackDistance), m_damage(damage), m_attackRate(attackRate), m_attackTiming(attackTiming)
{
}

MobAttackBehaviour::~MobAttackBehaviour()
{

}

bool MobAttackBehaviour::operator<(MobAttackBehaviour const& behaviour)
{
	return m_attackDistance < behaviour.m_attackDistance;
}

bool MobAttackBehaviour::isActive(Mob& mob)
{
	return mob.m_distanceToPlayer < m_attackDistance;
}

void MobAttackBehaviour::update(sf::Time dt)
{

}

void MobAttackBehaviour::createBody(Mob& mob)
{
}

void MobAttackBehaviour::activeAttackBox(Mob& mob, bool active)
{

}

void MobAttackBehaviour::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

int MobAttackBehaviour::getAttackDistance() const
{
	return m_attackDistance;
}

int MobAttackBehaviour::getDamage() const
{
	return m_damage;
}

int MobAttackBehaviour::getAttackRate() const
{
	return m_attackRate;
}
int MobAttackBehaviour::getAttackTiming() const
{
	return m_attackTiming;
}