#include "pch.h"
#include "Projectile.h"


Projectile::Projectile()
{
	m_projectileDef.shape.SetAsBox(1, 1, b2Vec2(0, 0), 0);
	m_projectileDef.bodyDef.type = b2_dynamicBody;
	m_projectileDef.bodyDef.bullet = true;
	m_projectileDef.fixtureDef.shape = &m_projectileDef.shape;
	m_projectileDef.fixtureDef.density = 0;

	m_projectileDef.circleShape = sf::CircleShape(3);
	m_projectileDef.circleShape.setFillColor(sf::Color::Yellow);

}

void Projectile::update()
{
	m_projectileDef.circleShape.setPosition(m_body->GetPosition().x, m_body->GetPosition().y);
}

void Projectile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_projectileDef.circleShape, states);
}


