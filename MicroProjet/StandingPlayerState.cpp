#include "pch.h"
#include <iostream>
#include "StandingPlayerState.h"
#include "RunningPlayerState.h"


StandingPlayerState::StandingPlayerState()
{
}

StatePtr StandingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	if (sfEvent.type == sf::Event::KeyReleased)
	{
		std::cout << "RELEASED" << std::endl;
	}

	if (sfEvent.type == sf::Event::KeyPressed)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::Z:
			return std::make_unique<JumpingPlayerState>();
			break;

		case sf::Keyboard::D:
			return std::make_unique<RunningPlayerState>(Direction::RIGHT);
			break;
		case sf::Keyboard::Q:
			return std::make_unique<RunningPlayerState>(Direction::LEFT);
			break;

		default:
			break;
		}
	}

	return NULL;
	
}

void StandingPlayerState::enter(Player& player)
{
	std::cout << "Standing state" << std::endl;
	player.setLinearVelocity(b2Vec2(0,0));
	//player.setSprite(standing)
}

