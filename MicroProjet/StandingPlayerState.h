#ifndef STANDINGPLAYERSTATE_H
#define STANDINGPLAYERSATET_H

#include "PlayerState.h"
#include "JumpingPlayerState.h"


class StandingPlayerState : public PlayerState
{
public:
	StandingPlayerState();
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) override;
	virtual void update(Player& player) override;
	void enter(Player& player);
	
};

#endif