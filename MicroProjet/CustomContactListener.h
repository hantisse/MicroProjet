#pragma once
#include <Box2D/Box2D.h>
#include <set>
#include "Player.h"

class CustomContactListener : public b2ContactListener
{
public:
	CustomContactListener();
	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void compute(FixtureContactData* contactDataA, FixtureContactData* contactDataB);

	std::set<b2Body*> toRemove;


};

