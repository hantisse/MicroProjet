#pragma once
#include "Mob.h"
#include "Projectile.h"

//Mobs that attack from afar with projectiles
class DistanceMob : public Mob
{
public:
	DistanceMob(EntityID id, tmx::Vector2f position);
	virtual void attack() override;
	virtual ~DistanceMob();

protected:
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	virtual void update(sf::Time dt) override;
};

