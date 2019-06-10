#pragma once
#include "Entity.h"


enum Direction
{
	LEFT,
	RIGHT,
};

//Entity that can die, attack
class LivingEntity : public Entity
{
public:
	LivingEntity(EntityID id);


	int getMaxVel() const; 
	int getJumpPower() const; 
	Direction getDirection() const;
	
	void applyDirectionImpulse();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	virtual void setDirection(Direction const direction);
	
	virtual void takeDamage(int damage) = 0;
	bool dead() const;
	
	virtual void attack() {};
	virtual void jump() {};

protected:
	LivingEntityModel const* getModel() const;

	int m_health;

	sf::RectangleShape m_lifeBar;
	sf::RectangleShape m_life;

	Direction m_direction;


};

