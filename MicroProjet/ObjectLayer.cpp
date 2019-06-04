#include "pch.h"
#include "ObjectLayer.h"


ObjectLayer::ObjectLayer(std::string const& name, tmx::Map const& map)
{
	tmx::ObjectGroup tmxLayer;
	for (auto const& layer : map.getLayers())
	{
		if (layer->getName() == name)
		{
			tmxLayer = layer->getLayerAs<tmx::ObjectGroup>();
		}
	}

	auto const& objects = tmxLayer.getObjects();
	for (auto const& object : objects) {
		b2BodyDef bodyDef;
		//bodyDef.position.Set(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y);
		bodyDef.position.Set(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y  + object.getAABB().height / 2);

		b2PolygonShape box;
		box.SetAsBox(object.getAABB().width / 2, object.getAABB().height / 2);

		m_bodyDefs.push_back(std::make_pair(bodyDef, box));


		//Debug

		sf::RectangleShape shape(sf::Vector2f(object.getAABB().width, object.getAABB().height));
		shape.setOrigin(object.getAABB().width / 2, object.getAABB().height / 2);

		shape.setPosition(object.getPosition().x + object.getAABB().width / 2, object.getPosition().y + object.getAABB().height / 2);
		shape.setFillColor(sf::Color::Cyan);
		shape.setOutlineColor(sf::Color::Cyan);
		m_shapes.push_back(shape);

		// fin debug
	}

}