#include "pch.h"
#include "DistanceMob.h"
#include "MobState.h"


DistanceMob::DistanceMob(EntityID id, int activationDistance, tmx::Vector2f position) :
	Mob(id, activationDistance, position)
{

}


void DistanceMob::update(sf::Time dt)
{
	Mob::update(dt);
	for (auto const& proj : m_projectiles)
		proj->update(dt);
}


void DistanceMob::attack()
{
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(FIRE_PROJECTILE, b2Vec2(m_body->GetPosition().x, m_body->GetPosition().y - 5));
	projectile->createBody(*m_body->GetWorld());

	projectile->setUserData(true, FIX_BULLET, &m_attackPower);

	double vel = m_direction == RIGHT ? 5. : -5.;
	projectile->setLinearVelocity(b2Vec2(vel, 0));

	m_projectiles.push_back(std::move(projectile));


}

DistanceMob::~DistanceMob() {};