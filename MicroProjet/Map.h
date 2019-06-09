#pragma once
#include <vector>
#include "SFMLOrthogonalLayer.hpp"
#include "CollisionLayer.h"
#include "ActivationLayer.h"
#include "Mob.h"

class Map : public sf::Drawable
{
public:
	Map() = default;
	Map(std::string path);
	void createBodies(b2World& b2World);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	auto& getLayers() { return m_tmxMap.getLayers(); }

private:
	std::vector<std::unique_ptr<MapLayer>> m_tiledLayers;
	CollisionLayer m_collisionLayer;
	ActivationLayer m_activationLayer;
	tmx::Map m_tmxMap;

	void createActivationBodies(b2World& world);
	void createCollisionBodies(b2World& world);
};

