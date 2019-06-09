#pragma once
#include <Box2D/Box2D.h>
#include <sfml/Graphics.hpp>
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(EntityID id, b2Vec2 position, int power);
	void destroy();
	bool destroyed();
private:
	void loadAnimations() override;

	bool m_destroyed;
		
};

