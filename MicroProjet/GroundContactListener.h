#pragma once
#include <Box2D/Box2D.h>
#include "Player.h"

class GroundContactListener : public b2ContactListener
{
public:
	GroundContactListener(Player* player);
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;

//private:
	Player* m_player;

};

