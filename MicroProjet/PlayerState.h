#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H
#include "Player.h"

class Player;

class PlayerState
{
public:
	PlayerState();
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) = 0;

	virtual void update(Player& player) {};
	virtual void enter(Player& player) = 0;
	virtual void exit(Player& player);

};

#endif