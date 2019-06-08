#include "pch.h"
#include <iostream>
#include "CustomContactListener.h"


CustomContactListener::CustomContactListener()
{
}

void CustomContactListener::BeginContact(b2Contact* contact) {
	FixtureContactData* fixtureUserDataA = static_cast<FixtureContactData*>(contact->GetFixtureA()->GetUserData());
	FixtureContactData* fixtureUserDataB = static_cast<FixtureContactData*>(contact->GetFixtureB()->GetUserData());

	if (fixtureUserDataA != nullptr)
	{
		compute(fixtureUserDataA, fixtureUserDataB);
	}
	
	if (fixtureUserDataB != nullptr)
	{
		compute(fixtureUserDataB, fixtureUserDataA);
	}

}

void CustomContactListener::compute(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case FIX_FOOT:
		++(*(contactDataA->data));
		break;
	case FIX_BULLET:
		
 		if (contactDataB != nullptr)
		{
			
			if (contactDataB->type == FIX_PLAYER)
			{
				*(contactDataB->data) -= *(contactDataA->data);
			}

			b2Body* body = static_cast<b2Body*>(contactDataA->origin);

			toRemove.insert(body);
			
		}
		break;
	case FIX_MOB:
		if (contactDataB != nullptr)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				*(contactDataB->data) -= *(contactDataA->data)/2;
			}

		}
		break;

	default:
		break;
	}
}

void CustomContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	FixtureContactData* fixtureUserData = static_cast<FixtureContactData*>(contact->GetFixtureA()->GetUserData());
	if (fixtureUserData != nullptr && fixtureUserData->type == FIX_FOOT)
	{
		--(*(fixtureUserData->data));
	}
	//check if fixture B was the foot sensor
	fixtureUserData = static_cast<FixtureContactData*>(contact->GetFixtureB()->GetUserData());
	if (fixtureUserData != nullptr && fixtureUserData->type == FIX_FOOT)
	{
		--(*(fixtureUserData->data));
	}
}