// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <string_view>
#include "Game.h"
#include "CollisionLayer.h"
#include "SFMLOrthogonalLayer.hpp"

#include "MobFireElemental.h"
#include "MobSlime.h"


using namespace std::literals::string_view_literals;

std::vector<EntityModelPtr>* GameEntityModels;


const float viewWidth = 400*1.2;
const float viewHeight = 300*1.2;
const int SCALE = 30;

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

Game::Game() :
	m_window(sf::VideoMode(800, 600), "SFML works!"),
	m_gameView(sf::Vector2f(viewHeight / 2, viewHeight / 2), sf::Vector2f(viewWidth, viewHeight)),
	m_gravity(0.0f, 0.7f),
	m_world(m_gravity),
	m_map("Assets/maps/mapTest3.tmx"),
	m_contactListener()
{

	createEntityModels();

	m_player = std::make_unique<Player>();

	m_map.createBodies(m_world);
	createMobBodies();
	m_player->createBody(m_world);
	m_world.SetContactListener(&m_contactListener);

	std::cout << "world : " << &m_world << std::endl;
}



void Game::run() {
	
	while (m_window.isOpen())
	{
		pollSFMLEvent();
		update();
		render();

	}
	
}

void Game::update() {
	
	sf::Time dt = m_clock.restart();

	m_world.Step(timeStep, velocityIterations, positionIterations);
	m_player->update(dt);
	updateMobs(dt);

	removeDeadObjects();

	m_gameView.setCenter(m_player->getPosition());
	m_window.setView(m_gameView);
}

void Game::updateMobs(sf::Time dt)
{
	for (auto& mob : m_mobs)
	{
		mob->updateDistToPlayer(m_player->getPosition());
		mob->update(dt);
	}
}

void Game::pollSFMLEvent() {
	while (m_window.pollEvent(m_sfEvent))
	{
		if (m_sfEvent.type == sf::Event::Closed) {
			m_window.close();
			return;
		} 
		else if(m_sfEvent.type == sf::Event::KeyPressed || m_sfEvent.type == sf::Event::KeyReleased)
		{
			m_player->handleInput(m_sfEvent);
		}
		
	}
}

void Game::render() 
{
	m_window.clear();
	m_window.draw(*m_player.get());
	renderMobs();

	m_window.draw(m_map);


	m_window.display();
}

void Game::renderMobs()
{

	for (auto const& mob : m_mobs)
	{
		m_window.draw(*mob.get());
	}
}


void Game::createMobBodies()
{
	createMobs();

	for (auto const& mob : m_mobs)
	{
		mob->createBody(m_world);
	}
}

void Game::createMobs()
{
	tmx::ObjectGroup spawnLayer;
	for (auto const& layer : m_map.getLayers())
	{
		if (layer->getName() == "SPAWN"sv)
		{
			spawnLayer = layer->getLayerAs<tmx::ObjectGroup>();
			break;
		}
	}

	for (auto const& object : spawnLayer.getObjects())
	{
		EntityID mobId = static_cast<EntityID>(std::atoi(object.getName().c_str()));
		switch (mobId)
		{
		case EntityID::FIRE_ELEMENTAL:

			m_mobs.push_back(std::make_unique<MobFireElemental>(tmx::Vector2f(
				object.getPosition().x + object.getAABB().width / 2,
				object.getPosition().y + object.getAABB().height / 2)));
			break;
		case EntityID::SLIME:
			m_mobs.push_back(std::make_unique<MobSlime>(tmx::Vector2f(
				object.getPosition().x + object.getAABB().width / 2,
				object.getPosition().y + object.getAABB().height / 2)));
		default:
			break;
		}
	}

}

void Game::removeDeadObjects()
{
	killDeadMobs();

	for (b2Body* body : m_contactListener.toRemove)
	{
		if (body != nullptr)
		{
			m_world.DestroyBody(body);
			std::cout << "remove body : " << body << std::endl;
		}
			
	}

	
	m_contactListener.toRemove.clear();
}

void Game::killDeadMobs()
{
	std::set<b2Body*> toDestroy;
	
	std::for_each(m_mobs.begin(), m_mobs.end(), [&toDestroy](auto& mob) { if (mob->dead() && !mob->isAnimationPlaying()) toDestroy.insert(mob->getBody());  });
	m_mobs.erase(std::remove_if(m_mobs.begin(), m_mobs.end(), [](auto const& mob) { return mob->dead() && !mob->isAnimationPlaying(); }), m_mobs.end());
	
	for (auto& mobBody : toDestroy)
	{
		if(mobBody != nullptr)
			m_world.DestroyBody(mobBody);
	}

}

void Game::createEntityModels()
{
	EntityModels = std::vector<EntityModelPtr>(EntityID::NB_ENTITY_ID);

	std::shared_ptr<EntityModel> player = std::make_shared<EntityModel>("Assets/images/player/adventurer.png");
		
	player->m_id = EntityID::PLAYER;
	player->m_bodyShape.SetAsBox(5.f, 10.f);
	player->m_bodyFixDef.shape = &player->m_bodyShape;
	player->m_bodyFixDef.filter.categoryBits = FIX_PLAYER;
	player->m_spriteRect = sf::IntRect(0, 0, 50, 36);
	
	EntityModels[EntityID::PLAYER] = player;

	std::shared_ptr<EntityModel> fire_elemental = std::make_shared<EntityModel>("Assets/images/mobs/fire_elemental.png");
	
	
	fire_elemental->m_id = EntityID::SLIME;
	fire_elemental->m_bodyShape.SetAsBox(4.f, 5.f);
	fire_elemental->m_bodyFixDef.shape = &fire_elemental->m_bodyShape;
	fire_elemental->m_bodyFixDef.density = 15.f;
	fire_elemental->m_bodyFixDef.filter.categoryBits = FIX_MOB;
	fire_elemental->m_spriteRect = sf::IntRect(0, 0, 32, 32);
	

	
	EntityModels[EntityID::FIRE_ELEMENTAL] = fire_elemental;

	std::shared_ptr<EntityModel> slime = std::make_shared<EntityModel>("Assets/images/mobs/slime.png");

	slime->m_id = EntityID::SLIME;
	slime->m_bodyShape.SetAsBox(8.f, 6.f);
	slime->m_bodyFixDef.shape = &slime->m_bodyShape;
	slime->m_bodyFixDef.density = 15.f;
	slime->m_bodyFixDef.filter.categoryBits = FIX_MOB;
	slime->m_spriteRect = sf::IntRect(0, 0, 32, 32);
	

	EntityModels[EntityID::SLIME] = slime;

	std::shared_ptr<EntityModel> projectile = std::make_shared<EntityModel>("Assets/images/mobs/fire_projectile.png");

	projectile->m_id = EntityID::FIRE_PROJECTILE;
	projectile->m_bodyShape.SetAsBox(3.f, 3.f);
	projectile->m_bodyFixDef.shape = &projectile->m_bodyShape;

	projectile->m_bodyFixDef.density = 0;
	projectile->m_bodyFixDef.filter.categoryBits = FIX_BULLET;
	projectile->m_bodyFixDef.filter.maskBits = FIX_PLAYER | FIX_WALL;
	projectile->m_bodyFixDef.isSensor = true;
	projectile->m_spriteRect = sf::IntRect(0, 0, 3, 3);

	EntityModels[EntityID::FIRE_PROJECTILE] = projectile;


	GameEntityModels = &EntityModels;
}


int monMain()
{


	Game game;
	game.run();

	return 0;
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
