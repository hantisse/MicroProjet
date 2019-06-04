#pragma once
#include "PlayerState.h"




class RunningPlayerState : public PlayerState
{
public:
	RunningPlayerState(Direction dir);
	virtual StatePtr handleInput(Player& player, sf::Event sfEvent) override;
	virtual void update(Player& player) override;
	void enter(Player& player);
private:
	Direction m_dir;
	void updatePlayerDirection(Player& player) const;
	void backFromJump();


	bool m_hasJumped;

};

