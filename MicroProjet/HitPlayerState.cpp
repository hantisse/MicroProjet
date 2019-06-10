#include "pch.h"
#include "HitPlayerState.h"
#include "DeadPlayerState.h"
#include "Mob.h"


HitPlayerState::HitPlayerState() :
	m_timeOut(0)
{
}

StatePtr HitPlayerState::handleInput(Player& player, sf::Event sfEvent)
{	
	return NULL;
}

void HitPlayerState::update(Player& player) 
{
	++m_timeOut;
	if (m_timeOut > 1000) exit(player);
}
void HitPlayerState::enter(Player& player)
{
	player.setImmune(true);
	player.playAnimation("idle");
	float impulse = player.getMass() * -.5f;
	int dir = player.getDirection() == RIGHT ? -1 : 1;
	player.applyLinearImpulseToCenter(b2Vec2(dir * player.getMass(), -1.f), true);
}
void HitPlayerState::exit(Player& player)
{
	player.setImmune(false);
	PlayerState::exit(player);
}
