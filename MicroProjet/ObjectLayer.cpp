#include "pch.h"
#include "ObjectLayer.h"


ObjectLayer::ObjectLayer(std::string const& name, tmx::Map const& map) :
	m_name(name)
{
	for (auto const& layer : map.getLayers())
	{
		if (layer->getName() == name)
		{
			m_tmxLayer = layer->getLayerAs<tmx::ObjectGroup>();
		}
	}

}