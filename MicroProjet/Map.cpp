#include "pch.h"
#include "Map.h"
#include <string_view>
#include <string>
#include "tmxlite/LayerGroup.hpp"

#include <string_view>
using namespace std::literals::string_view_literals;

Map::Map(std::string path) 
{
	m_tmxMap.load(path);

	for (int i = 0; i < m_tmxMap.getLayers().size(); ++i) {
		m_tiledLayers.push_back(std::make_unique<MapLayer>(m_tmxMap, i));
	}

	m_collisionLayer = CollisionLayer(m_tmxMap);
	m_activationLayer = ActivationLayer(m_tmxMap);

}
void Map::createBodies(b2World& world)
{
	createCollisionBodies(world);
	createActivationBodies(world);
	
}

void Map::createCollisionBodies(b2World& world)
{
	m_collisionLayer.createBodies(world);
}

void Map::createActivationBodies(b2World& world)
{
	m_activationLayer.createBodies(world);

}



void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& layer : m_tiledLayers) {
		target.draw(*layer.get(), states);
	}

}

