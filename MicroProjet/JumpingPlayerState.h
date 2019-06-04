#ifndef JUMPINGPLAYERSTATE_H
#define JUMPINGPLAYERSTATE_H

#include "PlayerState.h"

class JumpingPlayerState : public PlayerState
{
public:
	JumpingPlayerState();
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) override;
	virtual void enter(Player& player) override;
	virtual StatePtr exit(Player& player) override;
private:
	Direction m_dir;
	
};

#endif