#include "pch.h"
#include <iostream>
#include "RunningPlayerState.h"
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"



RunningPlayerState::RunningPlayerState(Direction dir) :
	m_dir(dir)
{

}

StatePtr RunningPlayerState::handleInput(Player& player, sf::Event sfEvent)
{

	if (sfEvent.type == sf::Event::KeyReleased)
	{
		
	}

	if (sfEvent.type == sf::Event::KeyPressed)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::Z:
			return std::make_unique<JumpingPlayerState>();
			break;

		case sf::Keyboard::D:
			m_dir = Direction::RIGHT;
			enter(player);
			//player.setSprite(right)
			break;
		case sf::Keyboard::Q:
			m_dir = Direction::LEFT;
			enter(player);
			//player.setSprite(right)
			break;

		default:
			break;
		}
	}
	else if (sfEvent.type == sf::Event::KeyReleased)
	{

		std::cout << "running RELEASED" << std::endl;
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::D:
		case sf::Keyboard::Q:

			return std::make_unique<StandingPlayerState>();
			//player.setSprite(right)
			break;
		default:
			break;
		}
	}

	return NULL;

}

void RunningPlayerState::enter(Player& player)
{
	b2Vec2 v = m_dir == Direction::RIGHT ? b2Vec2(8, 0) : b2Vec2(-8, 0);
	player.setLinearVelocity(v);
	//player.setSprite(standing)
}
