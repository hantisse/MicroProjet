#include "pch.h"
#include "ActivationLayer.h"
#include <string_view>
#include <iostream>
#include "Player.h"

using namespace std::literals::string_view_literals;


ActivationLayer::ActivationLayer(tmx::Map const& map) :
	ObjectLayer("ACTIVATION", map)
{
	m_bodyDefs = std::vector<std::pair<b2BodyDef, b2PolygonShape>>(NB_ACT_TYPES);
	m_contactDatas = std::vector<FixtureContactData>(NB_ACT_TYPES);

	auto const& objects = m_tmxLayer.getObjects();
	for (auto const& object : objects) {
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y + object.getAABB().height / 2);

		b2PolygonShape box;
		box.SetAsBox(object.getAABB().width / 2, object.getAABB().height / 2);

		if(object.getName() == "JUMP"sv)
			m_bodyDefs[JUMP] = std::make_pair(bodyDef, box);
		else if(object.getName() == "SHIELD"sv)
			m_bodyDefs[SHIELD] = std::make_pair(bodyDef, box);
		else if(object.getName() == "ATTACK"sv)
			m_bodyDefs[ATTACK] = std::make_pair(bodyDef, box);

		
		
	}
	
	m_contactDatas[JUMP] = { true, FIX_ACTIVATION, ACTIV_JUMP, nullptr };
	m_contactDatas[SHIELD] = { true, FIX_ACTIVATION, ACTIV_SHIELD, nullptr };
	m_contactDatas[ATTACK] = { true, FIX_ACTIVATION, ACTIV_ATTACK, nullptr };
	
}

void ActivationLayer::createBodies(b2World& world)
{
	
	b2FixtureDef fixDef;
	fixDef.filter.categoryBits = FIX_ACTIVATION;

	fixDef.isSensor = true;
	fixDef.userData = &(m_contactDatas[JUMP]);
	fixDef.shape = &(m_bodyDefs[JUMP].second);
	b2Body* body = world.CreateBody(&(m_bodyDefs[JUMP].first));
	body->CreateFixture(&fixDef);	
	std::cout << "Create body activation : " << body->GetPosition().x << std::endl;


	fixDef.userData = &(m_contactDatas[SHIELD]);
	fixDef.shape = &(m_bodyDefs[SHIELD].second);
	body = world.CreateBody(&(m_bodyDefs[SHIELD].first));
	body->CreateFixture(&fixDef);
	std::cout << "Create body activation : " << body->GetPosition().x << std::endl;

	fixDef.userData = &(m_contactDatas[ATTACK]);
	fixDef.shape = &(m_bodyDefs[ATTACK].second);
	body = world.CreateBody(&(m_bodyDefs[ATTACK].first));
	body->CreateFixture(&fixDef);
	

	std::cout << "Create body activation : "<<  body->GetPosition().x << std::endl;
		
}
