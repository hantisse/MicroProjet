#ifndef PLAYER_H
#define PLAYER_H


#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <stack>
#include "LivingEntity.h"

class PlayerState;
typedef std::unique_ptr<PlayerState> StatePtr;

enum activationCategories
{
	ACTIV_JUMP = 0x0001,
	ACTIV_SHIELD = 0x0002,
	ACTIV_ATTACK = 0x0004,
};

class Player : public LivingEntity 
{
public:
	Player();
	void createBody(b2World& world) override;
	int getNbFootContacts() { return m_nbFootContacts; }
	void incrNbFootContacts(int n = 1) { m_nbFootContacts += n; }
	void activeSword(bool active);
	void activeShield(bool active);
	void attack() override;

	void addActivation(unsigned short const flag);
	unsigned short getActivationFlags() const;

	void handleInput(sf::Event& sfEvent);
	void update(sf::Time dt) override;

	//Removes the first element of the stack of state : m_states
	void endState();
private:
	//Loads animations in the animator m_animator.
	//Called in the constructor.
	void loadAnimations() override;

	//Called in the createBody function, after the b2Body has been created. 
	//Initializes the sword and shield fixtures.
	void createWeaponHitBoxes(b2World& world);
	void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);

	int m_nbFootContacts;

	unsigned short m_activationFlags;

	//Stack of states of the players. Used for the player finite states machine.
	std::stack<StatePtr> m_states;

	b2PolygonShape m_footShape;
	b2FixtureDef m_footSensorFixDef;
	FixtureContactData m_footData;

	b2Fixture* m_swordFixRight;
	FixtureContactData m_swordRightData;
	b2Fixture* m_swordFixLeft;
	FixtureContactData m_swordLeftData;

	b2Fixture* m_shieldFixRight;
	FixtureContactData m_shieldRightData;
	b2Fixture* m_shieldFixLeft;
	FixtureContactData m_shieldLeftData;

		
};

#endif
