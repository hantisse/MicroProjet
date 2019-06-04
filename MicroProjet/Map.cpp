#include "pch.h"

#include "Map.h"



Map::Map(std::string path) 
{
	tmx::Map map;
	map.load(path);

	for (int i = 0; i < map.getLayers().size(); ++i) {
		m_tiledLayers.push_back(std::make_unique<MapLayer>(map, i));
	}

	m_collisionLayer = CollisionLayer(map);

}

void Map::createCollisionBodies(b2World& world)
{
	m_collisionLayer.createBodies(world);
}

void Map::update() 
{

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto const& layer : m_tiledLayers) {
		target.draw(*layer.get());
	}

	/*
	for (auto shape : m_collisionLayer.m_shapes) {
		target.draw(shape);
	}
	*/
	

}
