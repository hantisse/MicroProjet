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

enum GameState
{
	READY,
	RUNNING,
	PAUSED,
	INFO,
	LOST,
};

class Game {
public:
	Game();
	Game(std::string mapPath);

	//Game loop
	void run();

	void pollSFMLEvent();
	void update();
	void render();

	//Called before creating entities
	void createEntityModels();

	void changeMap(std::string const& mapPath);

	void createBodies();
	//CreateEntityModels needs to be called beforehand
	void createMobs();

	//Needs to be called after the mobs were created
	void createMobBodies();

	//Called in the update funtion
	void updateMobs(sf::Time dt);
	//Called in the render function
	void renderMobs();

	//Called to remove objects that were "killed" during the m_worl Step function
	void removeDeadObjects();
	//Called to remove mobs that are dead
	void removeDeadMobs();
	
	//Updates the UI of the player
	void updatePlayerUI();
	void updateInfoUI();
	std::vector<EntityModelPtr> EntityModels;

//private:
	sf::RenderWindow m_window;
	sf::View m_gameView;
	sf::Event m_sfEvent;
	sf::Text m_playerUI;
	sf::Text m_infoUI;
	sf::Font m_font;

	Map m_map;
	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<Mob>> m_mobs;

	b2Vec2 m_gravity; 
	b2World m_world;
	CustomContactListener m_contactListener;

	sf::Clock m_clock;

	GameState m_gameState;


};