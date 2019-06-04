#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stack>
#include "Entity.h"

class PlayerState;

typedef std::unique_ptr<PlayerState> StatePtr;

class Player : public Entity 
{
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	Player();
	void createBody(b2World& world) override;
	int getNbFootContacts() { return m_nbFootContacts; }
	void incrNbFootContact(int n = 1) { m_nbFootContacts += n; }
	void handleInput(sf::Event& sfEvent);
	void update(sf::Time dt) override;

	void endState();
private:

	virtual void loadAnimations() override;

	int m_nbFootContacts;
	std::stack<StatePtr> m_states;
	b2PolygonShape m_footShape;
	b2FixtureDef m_footSensorFixDef;
};

#endif
