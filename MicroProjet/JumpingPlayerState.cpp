#include "pch.h"
#include <iostream>
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"


JumpingPlayerState::JumpingPlayerState()
{
}

StatePtr JumpingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	if (player.getNbFootContacts() > 0) {
		//exit(player);
		return std::make_unique<StandingPlayerState>();
	}

	if (sfEvent.type == sf::Event::KeyPressed)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::D:
			player.setLinearVelocity(b2Vec2(8.f, 0));
			break;
		case sf::Keyboard::Q:
			player.setLinearVelocity(b2Vec2(-8.f, 0));

			break;

		default:
			break;
		}
		

	}
	
	return NULL;	
}


void JumpingPlayerState::enter(Player& player)
{
	player.applyLinearImpulseToCenter(b2Vec2(0, -8), true);
	//player.setSprite(jumping)
}

StatePtr JumpingPlayerState::exit(Player& player)
{
	return player.endState();
}
