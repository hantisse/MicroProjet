#pragma once
#include "PlayerState.h"

//State of blocking Player
class BlockingPlayerState : public PlayerState

{
public:
	BlockingPlayerState();
	StatePtr handleInput(Player& player, sf::Event sfEvent) override;

	void update(Player& player) override;
	void enter(Player& player) override;
	void exit(Player& player) override;

};

