#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "Player.h"

enum Direction
{
	LEFT,
	RIGHT,
	NONE,
	NBDIR
};

class Player;

class PlayerState
{
public:
	PlayerState();
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) = 0;
	virtual void update(Player& player) {};
	virtual void enter(Player& player) = 0;
	virtual StatePtr exit(Player& player) { return NULL; };

};

#endif