#pragma once
#include "PlayerState.h"

class HitPlayerState : public PlayerState
{
public:
	HitPlayerState();
	StatePtr handleInput(Player& player, sf::Event sfEvent) override;

	virtual void update(Player& player) override;
	virtual void enter(Player& player) override;
	virtual void exit(Player& player) override;
private:
	int m_timeOut;
};

