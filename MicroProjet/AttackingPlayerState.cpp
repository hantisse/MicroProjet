#include "pch.h"
#include "AttackingPlayerState.h"


AttackingPlayerState::AttackingPlayerState()
{
}


StatePtr AttackingPlayerState::handleInput(Player& player, sf::Event sfEvent)
{
	return NULL;
}
int timer = 0;

void AttackingPlayerState::update(Player& player)
{
	timer++;
	if (timer > 1000)
	{
		timer = 0;
		exit(player);
	}
}
		
void AttackingPlayerState::enter(Player& player)
{
	player.playAnimation("attack");
	player.activeSword(true);
	player.attack();

}

void AttackingPlayerState::exit(Player& player)
{
	player.activeSword(false);
	PlayerState::exit(player);
}
