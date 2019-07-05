#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <Thor/Animations.hpp>


enum EntityID
{
	PLAYER,
	FIRE_ELEMENTAL,
	SLIME,
	FIRE_PROJECTILE,
	NB_ENTITY_ID
};

//differentiates the differents EnityModel types
enum ModelType
{
	MOD_ENTITY,
	MOD_LIV,
	MOD_MOB,
};

enum AttackBehaviour
{
	BEHAV_DIST = 0x0001,
	BEHAV_CONTACT = 0x0002,
};

//Models created by the Game class, used to create similar entities
struct EntityModel
{
public:
	EntityModel(std::string const& texturePath);
	
	EntityID id;
	//type of the EntityModel. Check before downcasting
	ModelType type;

	//box2D shape of the b2body of the entity
	b2PolygonShape bodyShape;
	//box2D fixture definition of the b2body of the entity
	b2FixtureDef bodyFixDef;
	//rectangle indicating the sprite on the sprite sheet
	sf::IntRect spriteRect;
	//sprite sheet for the entity animator
	sf::Texture sourceTexture;
};

//Models created by the Game class, used to create similar entities
struct LivingEntityModel : EntityModel
{
	LivingEntityModel(std::string const& texturePath);
	//max health of the entity
	int maxHealth;
	//max velocity of the entity
	int maxVel;
	//impulse to apply to the entity body when it jumps. 0 means the entity can't jump.
	int jumpPower;
	//demage the entity does when it attacks
	int attackPower;
};

//Models created by the Game class, used to create similar entities
struct MobModel : LivingEntityModel
{
	MobModel(std::string const& texturePath);

	//behaviours to add
	unsigned short AttackBehaviourFilter;

	//distance to the player to enter attackingState
	int attackDist;
	//distante to the player to wake the mob. Moving mobs will move toward the player
	int wakeDistance;
	//time between two attacks
	int attackRate;
	//time before actually dealing the damage when the mob attacks
	int attackTiming;
	//origin of the sprite
	std::pair<int, int> spriteOrigin;
	//if the mob can move by itself
	bool canMove;

	//copied to the mob class
	thor::Animator<sf::Sprite, std::string> animator;
};

