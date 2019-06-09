#pragma once
#include <string>
#include <Box2D/Box2D.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Config.hpp>
#include "SFML/Graphics.hpp"
#include "Entity.h"

class ObjectLayer
{
public:
	ObjectLayer(std::string const& name, tmx::Map const& map);
	std::string getName() { return m_name; }
	virtual void createBodies(b2World& world) = 0;

	
protected:	
	ObjectLayer() = default;
	std::string m_name;
	tmx::ObjectGroup m_tmxLayer;

	std::vector<std::pair<b2BodyDef, b2PolygonShape>> m_bodyDefs;
	std::vector<FixtureContactData> m_contactDatas;
};

