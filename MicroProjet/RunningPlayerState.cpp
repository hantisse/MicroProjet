#include "pch.h"
#include <iostream>
#include "RunningPlayerState.h"
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"
#include "AttackingPlayerState.h"



RunningPlayerState::RunningPlayerState(Direction dir) :
	m_hasActed(false),
	m_timeOut(0)
{

}

StatePtr RunningPlayerState::handleInput(Player& player, sf::Event sfEvent)
{

	
	if (sfEvent.type == sf::Event::KeyPressed)
	{

		
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::Z:
			if (player.getNbFootContacts() > 0) {
				m_hasActed = true;;
				m_timeOut = 0;
				return std::make_unique<JumpingPlayerState>();
			}
			break;
		case sf::Keyboard::Enter:
			m_hasActed = true;;
			return std::make_unique<AttackingPlayerState>();
			break;
		case sf::Keyboard::D:
			player.setDirection(Direction::RIGHT);
			break;
		case sf::Keyboard::Q:
			player.setDirection(Direction::LEFT);
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

	
	//++m_timeOut;
	if (!player.isAnimationPlaying())
	{
		if (player.getNbFootContacts() < 1)// && m_timeOut > 500)
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
		backFromJump(player);
		m_hasActed = false;
	}

}

void RunningPlayerState::backFromJump(Player& player)
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
