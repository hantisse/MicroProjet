#ifndef JUMPINGPLAYERSTATE_H
#define JUMPINGPLAYERSTATE_H

#include "PlayerState.h"

//State of Player while jumping
class JumpingPlayerState : public PlayerState
{
public:
	JumpingPlayerState();
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) override;
	virtual void update(Player& player) override;
	virtual void enter(Player& player) override;
private:
	Direction m_dir;
	int m_jumpTimeOut = 0;
	int m_nbJumpLeft;
	
};

#endif