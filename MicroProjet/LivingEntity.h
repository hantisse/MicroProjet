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
	LivingEntity(std::string texturePath);

	int getMaxVel() { return m_maxVel; }
	int getJumpPower() { return m_jumpPower; }
	Direction getDirection() { return m_direction; }
	void applyDirectionImpulse();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	virtual void setDirection(Direction const direction);

	bool dead() { return m_health <= 0; };
	
	virtual void attack() {};
	virtual void jump() {};

protected:
	int m_maxHealth;
	int m_health;
	int m_maxVel;
	int m_jumpPower;
	int m_attackPower;

	sf::RectangleShape m_lifeBar;
	sf::RectangleShape m_life;

	Direction m_direction;


};

