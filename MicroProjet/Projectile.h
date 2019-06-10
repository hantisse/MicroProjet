#pragma once
#include <Box2D/Box2D.h>
#include <sfml/Graphics.hpp>
#include "Entity.h"

//Projectiles trown by entities
class Projectile : public Entity
{
public:
	Projectile(EntityID id, b2Vec2 position, int power);

	//Called when the projectile needs to be destroyed. Generally as a contact callback
	void destroy();

	//checks if the b2Body of the projectile has been destroyed .
	bool destroyed();
private:
	void loadAnimations() override;

	// true if the b2Body has been destroyed.
	bool m_destroyed;
		
};

