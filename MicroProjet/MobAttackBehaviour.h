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
	//called in the AttackingMobState class
	virtual void activeAttackBox(Mob& mob, bool active);

	//called in the AttackingMobState function
	virtual void attack(Mob const& mob) = 0;

	//called in the mob update function
	virtual void update(sf::Time dt);

	//called in the mob createBody function
	virtual void createBody(Mob& mob);

	//called in the mob draw function
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	//to sort the vector of MobAttackBehaviours : behaviours with the lower attack distance have priority
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

	//vector of projectiles the mob fired
	std::vector<std::unique_ptr<Projectile>> m_projectiles;


};