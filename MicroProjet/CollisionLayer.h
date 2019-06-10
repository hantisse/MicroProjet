#pragma once
#include "ObjectLayer.h"

//Layer of non-movable objects from the map that the entities should collide with
class CollisionLayer : public ObjectLayer
{
public: 
	CollisionLayer() = default;
	CollisionLayer(tmx::Map const& map);
	void createBodies(b2World& world) override;

};

