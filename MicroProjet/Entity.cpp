#include "pch.h"
#include <iostream>

#include "Entity.h"

extern std::vector<EntityModelPtr>* GameEntityModels;


Entity::Entity(EntityID id) :
	m_model((*GameEntityModels)[id])
{
	m_sprite = sf::Sprite(m_model->sourceTexture, m_model->spriteRect);
}

Entity::Entity(EntityID id, b2Vec2 position) :
	m_model((*GameEntityModels)[id])
{
	m_sprite = sf::Sprite(m_model->sourceTexture, m_model->spriteRect);
	m_bodyDef.position.Set(position.x, position.y);
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
	b2Fixture* fixture = m_body->CreateFixture(&m_model->bodyFixDef);
	fixture->SetUserData(&m_bodyData);
}

void Entity::applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake) 
{
	m_body->ApplyLinearImpulseToCenter(impulse, wake);
}

void Entity::setLinearVelocity(b2Vec2 const& impulse)
{
	m_body->SetLinearVelocity(impulse);
}

b2Vec2 Entity::getLinearVelocity() const
{
	return m_body->GetLinearVelocity();
}

float32 Entity::getMass() const
{
	return m_body->GetMass();
}






