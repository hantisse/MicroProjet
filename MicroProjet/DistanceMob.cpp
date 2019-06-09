#include "pch.h"
#include "DistanceMob.h"
#include "MobState.h"


DistanceMob::DistanceMob(EntityID id, tmx::Vector2f position) :
	Mob(id, position)
{
}


void DistanceMob::update(sf::Time dt)
{
	Mob::update(dt);
	m_projectiles.erase(std::remove_if(m_projectiles.begin(), m_projectiles.end(), [](auto const& proj) { return proj->destroyed(); }), m_projectiles.end());
	for (auto const& proj : m_projectiles)
		proj->update(dt);
}


void DistanceMob::attack()
{
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(FIRE_PROJECTILE, b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y - 5), getModel()->attackPower);
	projectile->createBody(*m_body->GetWorld());

	//projectile->setUserData(true, FIX_BULLET, &m_attackPower);

	double vel = m_direction == RIGHT ? 3. : -3.;
	projectile->setLinearVelocity(b2Vec2(vel, 0));

	m_projectiles.push_back(std::move(projectile));


}

DistanceMob::~DistanceMob() {};