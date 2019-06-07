#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stack>
#include "LivingEntity.h"

class PlayerState;
typedef std::unique_ptr<PlayerState> StatePtr;



class Player : public LivingEntity 
{
public:
	Player();
	void createBody(b2World& world) override;
	int getNbFootContacts() { return m_nbFootContacts; }
	void activeSword(bool active);
	void attack() override;

	void handleInput(sf::Event& sfEvent);
	void update(sf::Time dt) override;

	void endState();
private:

	void loadAnimations() override;
	void createSwordHitBoxes(b2World& world);
	void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);

	int m_nbFootContacts;
	std::stack<StatePtr> m_states;
	b2PolygonShape m_footShape;
	b2FixtureDef m_footSensorFixDef;
	FixtureContactData m_footData;

	b2Fixture* m_swordFixRight;
	FixtureContactData m_swordRightData;
	b2Fixture* m_swordFixLeft;
	FixtureContactData m_swordLeftData;

	
	b2DistanceJointDef m_swordJointDef;
	
};

#endif
