#include "pch.h"
#include <iostream>
#include "RunningPlayerState.h"
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"
#include "AttackingPlayerState.h"
#include "BlockingPlayerState.h"



RunningPlayerState::RunningPlayerState(Direction dir) :
	m_hasActed(false)
{

}

StatePtr RunningPlayerState::handleInput(Player& player, sf::Event sfEvent)
{

	
	if (sfEvent.type == sf::Event::KeyPressed)
	{

		
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::Z:
			if ((player.getActivationFlags() & ACTIV_JUMP) == ACTIV_JUMP
				&& player.getNbFootContacts() > 0) {
				m_hasActed = true;;
				return std::make_unique<JumpingPlayerState>();
			}
			break;
		case sf::Keyboard::Enter:
			if ((player.getActivationFlags() & ACTIV_ATTACK) == ACTIV_ATTACK)
			{
				m_hasActed = true;;
				return std::make_unique<AttackingPlayerState>();
			}
			break;
		case sf::Keyboard::D:
			player.setDirection(Direction::RIGHT);
			break;
		case sf::Keyboard::Q:
			player.setDirection(Direction::LEFT);
			break;
		case sf::Keyboard::P:
			if ((player.getActivationFlags() & ACTIV_SHIELD) == ACTIV_SHIELD)
			{
				m_hasActed = true;
				return std::make_unique<BlockingPlayerState>();
			}
			break;
		default:
			break;
		}
		
	}
	
	
	if (sfEvent.type == sf::Event::KeyReleased)
	{
		if(sfEvent.key.code == sf::Keyboard::D && player.getDirection() == Direction::RIGHT)
			exit(player);
		else if(sfEvent.key.code == sf::Keyboard::Q && player.getDirection() == Direction::LEFT)
			exit(player);
	}

	return NULL;

}

void RunningPlayerState::update(Player& player)
{
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)
		&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		exit(player);
		return;
	}

	
	if (!player.isAnimationPlaying())
	{
		if (player.getNbFootContacts() < 1)
		{
			player.playAnimation("fall");
		} 
		else
		{
			player.playAnimation("run");

		}

	}

	player.applyDirectionImpulse();


}

void RunningPlayerState::enter(Player& player)
{
	player.playAnimation("run");

	if (m_hasActed)
	{
		backFromAction(player);
		m_hasActed = false;
	}

}

void RunningPlayerState::backFromAction(Player& player)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && player.getDirection() == Direction::LEFT)
	{
		player.setDirection(Direction::RIGHT);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && player.getDirection() == Direction::RIGHT)
	{
		player.setDirection(Direction::LEFT);
	}
}

void RunningPlayerState::updatePlayerDirection(Player& player, Direction const direction) const
{
	player.setDirection(direction);


}
