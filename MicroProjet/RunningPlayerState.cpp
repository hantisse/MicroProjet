#include "pch.h"
#include <iostream>
#include "RunningPlayerState.h"
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"



RunningPlayerState::RunningPlayerState(Direction dir) :
	m_dir(dir),
	m_hasJumped(false)
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
				m_hasJumped = true;;
				return std::make_unique<JumpingPlayerState>();
			}
			break;

		case sf::Keyboard::D:
			m_dir = Direction::RIGHT;
			break;
		case sf::Keyboard::Q:
			m_dir = Direction::LEFT;
			break;

		default:
			break;
		}
		
	}
	
	
	if (sfEvent.type == sf::Event::KeyReleased)
	{
		if(sfEvent.key.code == sf::Keyboard::D && m_dir == Direction::RIGHT)
			exit(player);
		else if(sfEvent.key.code == sf::Keyboard::Q && m_dir == Direction::LEFT)
			exit(player);
	}

	return NULL;

}

void RunningPlayerState::update(Player& player)
{

	if (m_hasJumped)
	{
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)
			&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			exit(player);
			return;
		}
		
		m_hasJumped = false;
	}
		

	if (!player.isAnimationPlaying())
	{
		player.playAnimation("run");
	}

	updatePlayerDirection(player);



}

void RunningPlayerState::enter(Player& player)
{

	if (m_hasJumped)
	{
		backFromJump();

	}

}

void RunningPlayerState::backFromJump()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_dir == Direction::LEFT)
	{
		m_dir = RIGHT;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && m_dir == Direction::RIGHT)
	{
		m_dir = LEFT;
	}
}

void RunningPlayerState::updatePlayerDirection(Player& player) const
{
	
	player.setScale(m_dir == Direction::RIGHT ? sf::Vector2f(1, 1) : sf::Vector2f(-1, 1));
	player.setLinearVelocity(m_dir == Direction::RIGHT ? b2Vec2(8, 0) : b2Vec2(-8, 0));


}
