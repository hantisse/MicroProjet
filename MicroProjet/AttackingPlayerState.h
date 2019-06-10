#pragma once
#include "PlayerState.h"

//State of attacking Player
class AttackingPlayerState : public PlayerState
{
public:
	AttackingPlayerState();
	StatePtr handleInput(Player& player, sf::Event sfEvent) override;

	void update(Player& player) override;
	void enter(Player& player) override;
	void exit(Player& player) override;

};

