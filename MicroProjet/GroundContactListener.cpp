#include "pch.h"
#include <iostream>
#include "GroundContactListener.h"


GroundContactListener::GroundContactListener(Player* player) : m_player(player)
{
}

void GroundContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		m_player->incrNbFootContact();
	}
		
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
	{
		m_player->incrNbFootContact();
	}
		

}

void GroundContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == 3)
		m_player->incrNbFootContact(-1);
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == 3)
		m_player->incrNbFootContact(-1);
}