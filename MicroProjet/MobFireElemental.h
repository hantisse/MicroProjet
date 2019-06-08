#pragma once
#include "DistanceMob.h"


class MobFireElemental : public DistanceMob
{
public:
	MobFireElemental(tmx::Vector2f position);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void loadAnimations() override;

};

