#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>


enum EntityID
{
	PLAYER,
	FIRE_ELEMENTAL,
	SLIME,
	FIRE_PROJECTILE,
	NB_ENTITY_ID
};

class EntityModel
{
public:
	EntityModel() = default;
	EntityModel(std::string const& texturePath);
	
	EntityID m_id;

	b2PolygonShape m_bodyShape;
	b2FixtureDef m_bodyFixDef;
	sf::IntRect m_spriteRect;
	sf::Texture m_sourceTexture;
};

