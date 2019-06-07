#pragma once
#include <string>
#include <Box2D/Box2D.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/Config.hpp>
#include "SFML/Graphics.hpp"

class ObjectLayer
{
public:
	ObjectLayer(std::string const& name, tmx::Map const& map);
	std::string getName() { return m_name; }
	
protected:	
	ObjectLayer() = default;
	std::string m_name;
	tmx::ObjectGroup m_tmxLayer;

	std::vector<std::pair<b2BodyDef, b2PolygonShape>> m_bodyDefs;
	
	

};

