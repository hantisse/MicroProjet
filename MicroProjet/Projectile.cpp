#include "pch.h"
#include "Projectile.h"
#include <iostream>


Projectile::Projectile(EntityID id, b2Vec2 position) :
	Entity(id, position)
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.bullet = true;
	m_bodyDef.gravityScale = 0;

	loadAnimations();
	m_sprite.setOrigin(1.5f, 1.5f);
}

void Projectile::loadAnimations()
{
	thor::FrameAnimation fire;
	fire.addFrame(1.f, sf::IntRect(0, 32, 32, 32));

	m_animator.addAnimation("fire", fire, sf::seconds(1.f));
}
