#pragma once
#include "ObjectLayer.h"


class CollisionLayer : public ObjectLayer
{
public: 
	CollisionLayer() = default;
	CollisionLayer(tmx::Map const& map);
	void createBodies(b2World& world) override;

};

