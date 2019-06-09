#include "pch.h"
#include "BlockingPlayerState.h"


BlockingPlayerState::BlockingPlayerState()
{
}

StatePtr BlockingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{

	if (sfEvent.type == sf::Event::KeyReleased)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::P:
			exit(player);
			break;
		
		default:
			break;
		}
	}
	return NULL;
}


void BlockingPlayerState::update(Player& player)
{
}

void BlockingPlayerState::enter(Player& player)
{
	player.activeShield(true);

	player.playAnimation("block");
}



void BlockingPlayerState::exit(Player& player)
{
	player.activeShield(false);
	PlayerState::exit(player);
}
