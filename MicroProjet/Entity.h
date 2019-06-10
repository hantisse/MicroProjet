#pragma once
#include "EntityModel.h"

#include <Box2D/Box2D.h>
#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>

typedef std::shared_ptr<EntityModel> EntityModelPtr;

enum FixtureType {
	FIX_PLAYER = 0x0001,
	FIX_MOB = 0x0002,
	FIX_SWORD = 0x0004,
	FIX_FOOT = 0x0008,
	FIX_BULLET = 0x0010,
	FIX_MOB_ATTACK = 0x0020,
	FIX_WALL = 0x0040,
	FIX_SHIELD = 0x0080,
	FIX_ACTIVATION = 0x0100,
};


struct FixtureContactData
{
	bool active;
	FixtureType type;
	int data;
	void* origin;

};

class Entity : public sf::Drawable
{
protected:

	virtual void loadAnimations() = 0;
	EntityModelPtr m_model;

	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2Fixture* m_bodyFixture;
	//Data used if the b2Body enters in contact with another body
	FixtureContactData m_bodyData;

	sf::Sprite m_sprite;
	thor::Animator<sf::Sprite, std::string> m_animator;


public:


	Entity() = default;
	Entity(EntityID id);
	
	Entity(EntityID id, b2Vec2 bodyPosition);

	//First function to call after constructor
	virtual void createBody(b2World& world);

	b2Body* getBody() const { return m_body; }

	//Called by the Game update function
	virtual void update(sf::Time dt);

	//Called by the Game render function
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	//Play the animation. Interrupts the current animation
	void playAnimation(std::string animation);
	void stopAnimation();

	bool isAnimationPlaying();

	//To apply sudden change in the entity speed
	virtual void applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake);
	//To change the body speed
	void setLinearVelocity(b2Vec2 const& impulse);
	b2Vec2 getLinearVelocity() const;
	float32 getMass() const;
	const sf::Vector2f getPosition() { return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y); };

	
};

