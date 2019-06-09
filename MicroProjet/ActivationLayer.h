#pragma once
#include "ObjectLayer.h"


enum activationType
{
	JUMP,
	SHIELD,
	ATTACK,
	NB_ACT_TYPES
};

class ActivationLayer : public ObjectLayer
{
public:
	ActivationLayer() = default;
	ActivationLayer(tmx::Map const& map);
	void createBodies(b2World& world) override;
private:


};

