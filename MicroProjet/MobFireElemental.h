#pragma once

#include "Mob.h"

class Projectile;

class MobFireElemental : public Mob
{
public:
	MobFireElemental(tmx::Vector2f position);
	void attack() override;
	void createAttackHitBoxes(b2World& world) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void loadAnimations() override;
	std::vector<std::unique_ptr<Projectile>> m_projectiles;
	void update(sf::Time dt) override;

};

