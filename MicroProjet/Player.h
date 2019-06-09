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
	unsigned short getActivationFlags();

	void handleInput(sf::Event& sfEvent);
	void update(sf::Time dt) override;

	void endState();
private:

	void loadAnimations() override;
	void createWeaponHitBoxes(b2World& world);
	void computeAttack(FixtureContactData* contactDataA, FixtureContactData* contactDataB);

	int m_nbFootContacts;

	unsigned short m_activationFlags;

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
