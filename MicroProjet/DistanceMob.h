#pragma once
#include "Mob.h"
#include "Projectile.h"

class DistanceMob : public Mob
{
public:
	DistanceMob(EntityID id, int activationDistance, tmx::Vector2f position);
	virtual void attack() override;
	virtual ~DistanceMob();

protected:
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	virtual void update(sf::Time dt) override;
};

