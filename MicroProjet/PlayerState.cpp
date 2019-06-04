#include "pch.h"
#include "PlayerState.h"


PlayerState::PlayerState()
{
}

void PlayerState::exit(Player& player)
{
	player.stopAnimation();
	player.endState();
}
