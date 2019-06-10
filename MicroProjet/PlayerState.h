#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H
#include "Player.h"

//State of the player
class PlayerState
{
public:
	PlayerState();

	//Change the state of the Player depending on the input (sfEvent)
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) = 0;

	//Called in the update function of the player if this is the current player state
	virtual void update(Player& player) {};

	//Called when the player enter this state
	virtual void enter(Player& player) = 0;

	//Called when the player exits this state
	virtual void exit(Player& player);

};

#endif