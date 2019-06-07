#pragma once
#include <Box2D/Box2D.h>
#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>

enum FixtureType {
	PLAYER = 0x0001,
	MOB = 0x0002,
	SWORD = 0x0004,
	FOOT = 0x0008,
	BULLET = 0x0010,
	MOB_ATTACK = 0x0020,
};

struct EntityDef {
	b2BodyDef m_bodyDef;
	b2FixtureDef m_bodyFixDef;
	sf::IntRect m_spriteRect;
	sf::Texture m_sourceTexture;
};

struct FixtureContactData
{
	bool active;
	FixtureType type;
	int* data;
	void* origin;

};

class Entity : public sf::Drawable
{
protected:

	virtual void loadAnimations() = 0;

	b2Body* m_body;
	//EntityDef const& m_entityDef;
	b2BodyDef m_bodyDef;
	
	b2FixtureDef m_bodyFixDef;
	b2Fixture* m_bodyFixture;
	FixtureContactData m_bodyData;

	b2PolygonShape m_bodyShape;

	sf::IntRect m_spriteRect;
	sf::Texture m_sourceTexture;
	sf::Sprite m_sprite;

	thor::Animator<sf::Sprite, std::string> m_animator;


public:
	Entity() = default;
	//Entity(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef);
	Entity(std::string const& texturePath);
	//Entity(std::string const& texturePath, EntityDef const& entityDef);
	virtual void update(sf::Time dt);

	void playAnimation(std::string animation);
	void stopAnimation();
	bool isAnimationPlaying();

	virtual void createBody(b2World& world);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake);
	void setLinearVelocity(b2Vec2 const& impulse);
	b2Vec2 getLinearVelocity();
	float32 getMass();
	//void SetPosition(const sf::Vector2f& v);
	const sf::Vector2f getPosition() { return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y); };

	
};

