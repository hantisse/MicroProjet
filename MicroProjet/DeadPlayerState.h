#pragma once
#include "PlayerState.h"
class DeadPlayerState : public PlayerState
{
public:
	DeadPlayerState();
	StatePtr handleInput(Player& player, sf::Event sfEvent) override;

	virtual void update(Player& player) override;
	virtual void enter(Player& player) override;
	virtual void exit(Player& player) override;
};

