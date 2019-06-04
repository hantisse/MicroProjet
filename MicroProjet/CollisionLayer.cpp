#include "pch.h"
#include "CollisionLayer.h"
#include <iostream>
#include <string_view>
using namespace std::literals::string_view_literals;

CollisionLayer::CollisionLayer(tmx::Map const& map) :
	ObjectLayer("COLLISION", map)
{
	
	
		
}

void CollisionLayer::createBodies(b2World& world)
{
	for (auto const& pair : m_bodyDefs)
	{
		b2Body* body = world.CreateBody(&(pair.first));
		body->CreateFixture(&(pair.second), 0.0f);

	}
}
