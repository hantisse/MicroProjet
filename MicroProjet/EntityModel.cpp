#include "pch.h"
#include "EntityModel.h"
#include <iostream>


EntityModel::EntityModel(std::string const& texturePath)
{
	type = MOD_ENTITY;
	if (!sourceTexture.loadFromFile(texturePath))
	{
		std::cout << "Texture could not be loaded" << std::endl;
	}
	
}


LivingEntityModel::LivingEntityModel(std::string const& texturePath)
	:EntityModel(texturePath)
{
	type = MOD_LIV;
}


MobModel::MobModel(std::string const& texturePath) 
	:LivingEntityModel(texturePath)
{
	type = MOD_MOB;
}
