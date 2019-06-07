#pragma once
#include <Box2D/Box2D.h>
#include <sfml/Graphics.hpp>
#include "Entity.h"

struct ProjectileDef
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape shape;
	int damage;
	int maxVelocity;
	sf::CircleShape circleShape;
	FixtureContactData data;
};

class Projectile : public sf::Drawable
{
public:
	Projectile();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	ProjectileDef m_projectileDef;
	b2Body* m_body;
	void update();

		
};

