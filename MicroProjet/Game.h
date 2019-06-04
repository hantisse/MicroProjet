#pragma once
#include <ctime>
#include <cstdlib>
#include "SFML/Graphics.hpp"
#include <Box2D/Box2D.h>
#include "Thor/Resources.hpp"
#include "tmxlite/Map.hpp"

#include "Player.h"
#include "SFMLOrthogonalLayer.hpp"
#include "CollisionLayer.h"
#include "Map.h"
#include "GroundContactListener.h"


int monMain();

class Game {
public:
	//static thor::ResourceHolder<sf::Texture, std::string> holder;
	//static thor::ResourceHolder<tmx::Map, std::string> mapHolder;
	//static std::vector<std::unique_ptr<EntityDef>> entities;

	Map m_map;

	std::unique_ptr<Player> m_player;

	Game();
	void run();

private:
	sf::RenderWindow m_window;
	sf::View m_gameView;
	sf::Event m_sfEvent;

	b2Vec2 m_gravity; 
	b2World m_world;
	GroundContactListener m_contactListener;

	sf::Clock m_clock;
	float m_dt;

	void updateDt();
	void pollSFMLEvent();
	void update();
	void render();
};