#include "pch.h"
#include "CollisionLayer.h"
#include <iostream>
#include <string_view>
using namespace std::literals::string_view_literals;

CollisionLayer::CollisionLayer(tmx::Map const& map) :
	ObjectLayer("COLLISION", map)
{
	

	auto const& objects = m_tmxLayer.getObjects();
	for (auto const& object : objects) {
		b2BodyDef bodyDef;
		//bodyDef.position.Set(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y);
		bodyDef.position.Set(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y + object.getAABB().height / 2);

		b2PolygonShape box;
		box.SetAsBox(object.getAABB().width / 2, object.getAABB().height / 2);

		m_bodyDefs.push_back(std::make_pair(bodyDef, box));


	}
		
}

void CollisionLayer::createBodies(b2World& world)
{
	for (auto const& pair : m_bodyDefs)
	{
		b2Body* body = world.CreateBody(&(pair.first));
		body->CreateFixture(&(pair.second), 0.0f);

	}
}
