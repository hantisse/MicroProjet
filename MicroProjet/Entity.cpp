#include "pch.h"
#include <iostream>
#include "Entity.h"

Entity::Entity(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef)
{

}

void Entity::update() 
{
	this->m_sfShape.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
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




