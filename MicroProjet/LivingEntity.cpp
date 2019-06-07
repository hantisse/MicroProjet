#include "pch.h"
#include "LivingEntity.h"


LivingEntity::LivingEntity(std::string texturePath) :
	Entity(texturePath), m_direction(Direction::RIGHT),
	m_lifeBar(sf::RectangleShape(sf::Vector2f(40, 2))),
	m_life(sf::RectangleShape(sf::Vector2f(40, 2)))
{
	m_lifeBar.setFillColor(sf::Color::Red);
	m_lifeBar.setOrigin(20, 0);
	m_life.setFillColor(sf::Color::Green);
}

void LivingEntity::applyDirectionImpulse()
{
	setLinearVelocity(m_direction == Direction::RIGHT ? b2Vec2(m_maxVel, getLinearVelocity().y) : b2Vec2(-m_maxVel, getLinearVelocity().y));

}

void LivingEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
	target.draw(m_lifeBar);
	target.draw(m_life);
}


void LivingEntity::setDirection(Direction const direction)
{
	m_direction = direction;
	switch (direction)
	{
	case RIGHT:
		m_sprite.setScale(sf::Vector2f(1, 1));
		break;
	case LEFT:
		m_sprite.setScale(sf::Vector2f(-1, 1));
		break;
	default: break;

	}
}

