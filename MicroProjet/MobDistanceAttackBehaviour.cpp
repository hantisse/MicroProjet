#include "pch.h"
#include "MobDistanceAttackBehaviour.h"
#include "Projectile.h"
#include "Mob.h"
#include <iostream>


MobDistanceAttackBehaviour::MobDistanceAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming) : 
	MobAttackBehaviour(attackDistance, damage, attackRate, attackTiming)
{
}


MobDistanceAttackBehaviour::~MobDistanceAttackBehaviour()
{
}


void MobDistanceAttackBehaviour::attack(Mob const& mob)
{
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(FIRE_PROJECTILE, b2Vec2(mob.getBody()->GetPosition().x, mob.getBody()->GetPosition().y - 5), mob.getModel()->attackPower);
	projectile->createBody(*mob.getBody()->GetWorld());

	double vel = mob.getDirection() == RIGHT ? 3. : -3.;
	projectile->setLinearVelocity(b2Vec2(vel, 0));

	m_projectiles.push_back(std::move(projectile));

}

void MobDistanceAttackBehaviour::update(sf::Time dt)
{
	m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](auto const& proj) { return proj->destroyed(); }), m_projectiles.end());
	for (auto const& proj : m_projectiles)
		proj->update(dt);
}

void MobDistanceAttackBehaviour::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& proj : m_projectiles)
	{
		proj->draw(target, states);
	}
}


