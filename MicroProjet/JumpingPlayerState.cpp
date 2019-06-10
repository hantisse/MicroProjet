#include "pch.h"
#include <iostream>
#include "JumpingPlayerState.h"
#include "StandingPlayerState.h"


JumpingPlayerState::JumpingPlayerState() : 
	m_nbJumpLeft(1)
{
}

StatePtr JumpingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	
	if (sfEvent.type == sf::Event::KeyPressed)
	{
		switch (sfEvent.key.code)
		{
		
		case sf::Keyboard::Z:
			m_jumpTimeOut = 0;
			if (m_nbJumpLeft > 0)
			{
				--m_nbJumpLeft;

				player.setLinearVelocity(b2Vec2(player.getLinearVelocity().x, 0));
				float impulse = player.getMass() * -player.getJumpPower();
				player.applyLinearImpulseToCenter(b2Vec2(0, impulse), true);
				player.playAnimation("jump");
			}
			break;
		case sf::Keyboard::D:
			player.setDirection(Direction::RIGHT);
			player.setLinearVelocity(b2Vec2(player.getMaxVel()/2, player.getLinearVelocity().y));
			break;
		case sf::Keyboard::Q:
			player.setDirection(Direction::LEFT);
			player.setLinearVelocity(b2Vec2(-player.getMaxVel() / 2.f, player.getLinearVelocity().y));

			break;

		default:
			break;
		}
		

	}
	else if (sfEvent.type == sf::Event::KeyReleased)
	{
		switch (sfEvent.key.code)
		{
		case sf::Keyboard::D:
			player.setLinearVelocity(b2Vec2(player.getLinearVelocity().x / 2, player.getLinearVelocity().y));
			break;
		case sf::Keyboard::Q:
			player.setLinearVelocity(b2Vec2(player.getLinearVelocity().x / 2, player.getLinearVelocity().y));

			break;

		default:
			break;
		}
	}
	
	return NULL;	
}

void JumpingPlayerState::update(Player& player)
{
	++m_jumpTimeOut;

	if (m_jumpTimeOut > 500 && player.getNbFootContacts() > 0) {
		exit(player);
	}
	if (m_jumpTimeOut > 3000)
		exit(player);



}

void JumpingPlayerState::enter(Player& player)
{
	float impulse = player.getMass() * -player.getJumpPower();
	player.applyLinearImpulseToCenter(b2Vec2(0, impulse), true);
	player.playAnimation("jump");
}
