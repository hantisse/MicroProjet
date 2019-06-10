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
	//Called to make the player direction correspond to the current keyboard input
	void updatePlayerDirection(Player& player, Direction direction) const;

	//Called when entering this state if the state that exited was stacked on top of it.
	void backFromAction(Player& player);
	bool m_hasActed;

};

