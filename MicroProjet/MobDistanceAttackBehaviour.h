#pragma once
#include "MobAttackBehaviour.h"

class MobDistanceAttackBehaviour : public MobAttackBehaviour
{
public:
	MobDistanceAttackBehaviour(int attackDistance, int damage, int attackRate, int attackTiming);
	~MobDistanceAttackBehaviour();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void update(sf::Time dt) override;
	void attack(Mob const& mob) override;
};

