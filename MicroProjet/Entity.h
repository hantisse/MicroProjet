#pragma once
#include <Box2D/Box2D.h>
#include <Thor/Animations.hpp>
#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
protected:

	virtual void loadAnimations() = 0;

	b2Body* m_body;
	b2BodyDef m_bodyDef;
	
	b2FixtureDef m_bodyFixDef;

	b2PolygonShape m_bodyShape;

	sf::IntRect m_spriteRect;
	sf::Texture m_sourceTexture;
	sf::Sprite m_sprite;

	thor::Animator<sf::Sprite, std::string> m_animator;

public:
	Entity() = default;
	Entity(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef);
	virtual void update(sf::Time dt);

	void playAnimation(std::string animation);
	void stopAnimation();
	bool isAnimationPlaying();

	virtual void createBody(b2World& world);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake);
	void setLinearVelocity(b2Vec2 const& impulse);
	void setScale(sf::Vector2f scale);
	b2Vec2 getLinearVelocity();
	float32 getMass();
	//void SetPosition(const sf::Vector2f& v);
	const sf::Vector2f getPosition() { return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y); };

	
};

