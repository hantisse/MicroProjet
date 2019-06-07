#include "pch.h"
#include <iostream>
#include "StandingPlayerState.h"
#include "RunningPlayerState.h"
#include "AttackingPlayerState.h"


StandingPlayerState::StandingPlayerState()
{
}

StatePtr StandingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	
	if (sfEvent.type == sf::Event::KeyPressed)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::Z:
			if (player.getNbFootContacts() > 0) {
				return std::make_unique<JumpingPlayerState>();
			}
			break;
		case sf::Keyboard::Enter:
			return std::make_unique<AttackingPlayerState>();
			break;
		case sf::Keyboard::D:
			player.setDirection(Direction::RIGHT);
			return std::make_unique<RunningPlayerState>(Direction::RIGHT);
			break;
		case sf::Keyboard::Q:
			player.setDirection(Direction::LEFT);
			return std::make_unique<RunningPlayerState>(Direction::LEFT);
			break;

		default:
			break;
		}
	}

	


	return NULL;
	
}

void StandingPlayerState::update(Player& player)
{
	if (!player.isAnimationPlaying())
	{
		player.playAnimation("idle");
	}
}

void StandingPlayerState::enter(Player& player)
{
	player.setLinearVelocity(b2Vec2(0,0));
}

