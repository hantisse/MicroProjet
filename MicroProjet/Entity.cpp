#include "pch.h"
#include <iostream>
#include "Entity.h"


Entity::Entity(std::string const& texturePath)//, EntityDef const& entityDef)
{
	if (!m_sourceTexture.loadFromFile(texturePath))
	{
		std::cout << "Sprite could not be loaded" << std::endl;
	}
}

void Entity::update(sf::Time dt) 
{
	//this->m_sfShape.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
	m_sprite.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
	m_animator.update(dt);
	m_animator.animate(m_sprite);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void Entity::playAnimation(std::string animation)
{
	m_animator.playAnimation(animation);
}

void Entity::stopAnimation()
{
	m_animator.stopAnimation();
}

bool Entity::isAnimationPlaying()
{
	return m_animator.isPlayingAnimation();
}


void Entity::createBody(b2World& world) 
{
	m_body = world.CreateBody(&m_bodyDef);
	m_body->CreateFixture(&m_bodyFixDef);
}

void Entity::applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake) 
{
	m_body->ApplyLinearImpulseToCenter(impulse, wake);
}

void Entity::setLinearVelocity(b2Vec2 const& impulse)
{
	m_body->SetLinearVelocity(impulse);
}

b2Vec2 Entity::getLinearVelocity()
{
	return m_body->GetLinearVelocity();
}

float32 Entity::getMass()
{
	return m_body->GetMass();
}






