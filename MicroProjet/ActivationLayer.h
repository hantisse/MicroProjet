#pragma once
#include "ObjectLayer.h"


enum activationType
{
	JUMP,
	SHIELD,
	ATTACK,
	NB_ACT_TYPES
};

// Layer of sensors enabling the Player's capacities
class ActivationLayer : public ObjectLayer
{
public:
	ActivationLayer() = default;
	ActivationLayer(tmx::Map const& map);
	void createBodies(b2World& world) override;

};

