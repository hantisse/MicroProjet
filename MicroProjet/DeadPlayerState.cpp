#include "pch.h"
#include "DeadPlayerState.h"


DeadPlayerState::DeadPlayerState()
{
}


StatePtr DeadPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	return NULL;
}

void DeadPlayerState::update(Player& player)
{
	
}
void DeadPlayerState::enter(Player& player)
{
	player.playAnimation("die");
}
void DeadPlayerState::exit(Player& player)
{
}
