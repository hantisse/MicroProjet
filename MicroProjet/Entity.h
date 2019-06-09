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
	FixtureContactData m_bodyData;

	sf::Sprite m_sprite;
	thor::Animator<sf::Sprite, std::string> m_animator;


public:


	Entity() = default;
	Entity(EntityID id);
	
	Entity(EntityID id, b2Vec2 bodyPosition);
	virtual void update(sf::Time dt);

	void playAnimation(std::string animation);
	void stopAnimation();
	bool isAnimationPlaying();

	virtual void createBody(b2World& world);
	b2Body* getBody() { return m_body; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake);
	void setLinearVelocity(b2Vec2 const& impulse);
	void setUserData(bool active, FixtureType type, int* data);
	b2Vec2 getLinearVelocity();
	float32 getMass();
	//void SetPosition(const sf::Vector2f& v);
	const sf::Vector2f getPosition() { return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y); };

	
};

