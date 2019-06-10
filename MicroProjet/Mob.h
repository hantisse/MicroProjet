#pragma once
#include "LivingEntity.h"
#include <tmxlite/Types.hpp>
#include <stack>
#include <string>

class MobState;
typedef std::unique_ptr<MobState> MobStatePtr;


class Mob : public LivingEntity
{
public:
	Mob(EntityID id, tmx::Vector2f position);
	virtual void update(sf::Time dt) override;
	void updateDistToPlayer(sf::Vector2f playerPos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	b2Body* getBody() const;

	virtual void activeAttackBox(bool active) {};
	bool canAttack() const; 
	bool canMove() const;
	bool awake() const;
	int getAttackRate() const;
	int getAttackTiming() const;
	void takeDamage(int damage) override;

protected:
	//Updated during each loop
	int m_distanceToPlayer;

	MobModel const* getModel() const;
	void handlePlayerPos();

	MobStatePtr m_state;

};

