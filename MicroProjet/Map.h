#pragma once
#include <vector>
#include "SFMLOrthogonalLayer.hpp"

#include "CollisionLayer.h"

class Map : public sf::Drawable
{
public:
	Map() = default;
	Map(std::string path);
	void createCollisionBodies(b2World& world);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update();

private:
	std::vector<std::unique_ptr<MapLayer>> m_tiledLayers;
	CollisionLayer m_collisionLayer;
};

