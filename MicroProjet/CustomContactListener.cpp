#include "pch.h"
#include <iostream>
#include "CustomContactListener.h"
#include "Projectile.h"


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

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	

}

void CustomContactListener::compute(FixtureContactData* contactDataA, FixtureContactData* contactDataB)
{
	switch (contactDataA->type)
	{
	case FIX_FOOT:
		if (contactDataB != nullptr)
		{
			Player* player = static_cast<Player*>(contactDataA->origin);
			player->incrNbFootContacts();

		}
		
		break;
	case FIX_BULLET:
		
 		if (contactDataB != nullptr && contactDataB->active)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				Player* player = static_cast<Player*>(contactDataB->origin);
				player->takeDamage(contactDataA->data);
			}

			
			Projectile* bullet = static_cast<Projectile*>(contactDataA->origin);
			bullet->destroy();
			toRemove.insert(bullet->getBody());
			
		}
		break;
	case FIX_MOB:
		if (contactDataB != nullptr)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				//*(contactDataB->data) -= *(contactDataA->data)/2;
			}

		}
		break;

	case FIX_ACTIVATION:

		if (contactDataB != nullptr)
		{

			if (contactDataB->type == FIX_PLAYER)
			{
				Player* player = static_cast<Player*>(contactDataB->origin);
				player->addActivation((unsigned short)(contactDataA->data));
				std::cout << "activation" << (int)contactDataA->data << std::endl;
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
		Player* player = static_cast<Player*>(fixtureUserData->origin);
		player->incrNbFootContacts(-1);
	}
	//check if fixture B was the foot sensor
	fixtureUserData = static_cast<FixtureContactData*>(contact->GetFixtureB()->GetUserData());
	if (fixtureUserData != nullptr && fixtureUserData->type == FIX_FOOT)
	{
		Player* player = static_cast<Player*>(fixtureUserData->origin);
		player->incrNbFootContacts(-1);
	}
}