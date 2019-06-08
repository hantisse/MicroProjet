#pragma once
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>
#include "Thor/Resources.hpp"
#include "tmxlite/Map.hpp"

#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "CollisionLayer.h"
#include "Map.h"
#include "CustomContactListener.h"
#include "EntityModel.h"

int monMain();

class EntityModel;
typedef std::shared_ptr<EntityModel> EntityModelPtr;

class Game {
public:
	Game();
	void run();


	std::vector<EntityModelPtr> EntityModels;
	void pollSFMLEvent();
	void update();
	void render();

	void createEntityModels();

	void createMobs();
	void createMobBodies();
	void updateMobs(sf::Time dt);
	void renderMobs();

	void removeDeadObjects();
	void killDeadMobs();

private:
	sf::RenderWindow m_window;
	sf::View m_gameView;
	sf::Event m_sfEvent;

	Map m_map;
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Mob>> m_mobs;



	b2Vec2 m_gravity; 
	b2World m_world;
	CustomContactListener m_contactListener;

	sf::Clock m_clock;

	

};