#pragma once
#include <Box2D/Box2D.h>
#include <sfml/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(EntityID id, b2Vec2 position);
private:
	void loadAnimations() override;
		
};

