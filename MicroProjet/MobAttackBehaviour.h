#pragma once
#include "Player.h"
#include "Projectile.h"

class Mob;

class MobAttackBehaviour : sf::Drawable
{
public:
	MobAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming);
	virtual ~MobAttackBehaviour();

	bool isActive(Mob& mob);
	virtual void activeAttackBox(Mob& mob, bool active);
	virtual void attack(Mob const& mob) = 0;
	virtual void update(sf::Time dt);
	virtual void createBody(Mob& mob);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	bool operator<(MobAttackBehaviour const& behaviour);

	int getAttackDistance() const;
	int getDamage() const;
	int getAttackRate() const;
	int getAttackTiming() const;

protected:
	int m_attackDistance;
	int m_damage;
	int m_attackRate;
	int m_attackTiming;

	std::vector<std::unique_ptr<Projectile>> m_projectiles;


};