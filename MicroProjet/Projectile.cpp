#include "pch.h"
#include "Projectile.h"
#include <iostream>


Projectile::Projectile(EntityID id, b2Vec2 position, int power ) :
	Entity(id, position)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.bullet = true;
	m_bodyDef.gravityScale = 0;

	m_bodyData = { true, FIX_BULLET, power, this };

	loadAnimations();
	m_sprite.setOrigin(1.5f, 1.5f);
}

void Projectile::loadAnimations()
{
	thor::FrameAnimation fire;
	fire.addFrame(1.f, sf::IntRect(0, 32, 32, 32));

	m_animator.addAnimation("fire", fire, sf::seconds(1.f));
}

void Projectile::destroy()
{
	m_destroyed = true;
}

bool Projectile::destroyed()
{
	return m_destroyed;
}