#include "pch.h"
#include "EntityModel.h"
#include <iostream>


EntityModel::EntityModel(std::string const& texturePath)
{
	
	if (!m_sourceTexture.loadFromFile(texturePath))
	{
		std::cout << "Texture could not be loaded" << std::endl;
	}
	
}

