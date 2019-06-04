#pragma once
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
protected:
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	
	b2FixtureDef m_bodyFixDef;

	b2PolygonShape m_bodyShape;
	sf::RectangleShape m_sfShape;

	//std::shared_ptr<sf::Texture> texture;
	//sf::Sprite m_sprite;

public:
	Entity() = default;
	Entity(b2BodyDef& bodyDef, b2FixtureDef& fixtureDef);
	virtual void createBody(b2World& world);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	virtual void applyLinearImpulseToCenter(b2Vec2 const& impulse, bool wake);
	virtual void setLinearVelocity(b2Vec2 const& impulse);
	virtual void update();
	//void SetPosition(const sf::Vector2f& v);
	const sf::Vector2f getPosition() { return sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y); };
	
};

