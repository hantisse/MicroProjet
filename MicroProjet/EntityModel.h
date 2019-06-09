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

enum ModelType
{
	MOD_ENTITY,
	MOD_LIV,
	MOD_MOB,
};

struct EntityModel
{
public:
	//EntityModel() = default;
	EntityModel(std::string const& texturePath);
	
	EntityID id;
	ModelType type;

	b2PolygonShape bodyShape;
	b2FixtureDef bodyFixDef;
	sf::IntRect spriteRect;
	sf::Texture sourceTexture;
};

struct LivingEntityModel : EntityModel
{
	LivingEntityModel(std::string const& texturePath);

	int maxHealth;
	int maxVel;
	int jumpPower;
	int attackPower;
};

struct MobModel : LivingEntityModel
{
	MobModel(std::string const& texturePath);

	int attackDist;
	int wakeDistance;
	int attackRate;
	int attackTiming;
	bool canMove;
};

