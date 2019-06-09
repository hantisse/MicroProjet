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
	//virtual void createAttackHitBoxes(b2World& world) = 0;

	b2Body* getBody() { return m_body; };

	virtual void activeAttackBox(bool active) {};
	bool canAttack(); 
	bool canMove();
	bool awake();
	int getAttackRate();
	int getAttackTiming();
	void hitByPlayer(int damage);

protected:

	/*
	int m_distanceToPlayer;
	const int m_attackDist;
	int m_wakeDistance;
	int m_attackRate;
	int m_attackTiming;
	bool m_canMove;
	*/
	int m_distanceToPlayer;

	MobModel const* getModel();
	void handlePlayerPos();

	MobStatePtr m_state;

};

