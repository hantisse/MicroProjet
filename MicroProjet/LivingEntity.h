#pragma once
#include "Entity.h"


enum Direction
{
	LEFT,
	RIGHT,
};

class LivingEntity : public Entity
{
public:
	LivingEntity(EntityID id);

	int getMaxVel(); 
	int getJumpPower(); 
	Direction getDirection() { return m_direction; }
	LivingEntityModel* getModel();
	void applyDirectionImpulse();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	virtual void setDirection(Direction const direction);

	bool dead() { return m_health <= 0; };
	
	virtual void attack() {};
	virtual void jump() {};

protected:
	/*
	int m_maxHealth;
	int m_maxVel;
	int m_jumpPower;
	int m_attackPower;
	*/
	int m_health;

	sf::RectangleShape m_lifeBar;
	sf::RectangleShape m_life;

	Direction m_direction;


};

