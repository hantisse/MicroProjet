// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Game.h"
#include "CollisionLayer.h"
#include "SFMLOrthogonalLayer.hpp"
#include "DebugDraw.h"

DebugDraw dd;

const float viewWidth = 400*1.2;
const float viewHeight = 300*1.2;
const int SCALE = 30;

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

Game::Game() :
	m_window(sf::VideoMode(800, 600), "SFML works!"),
	m_gameView(sf::Vector2f(viewHeight / 2, viewHeight / 2), sf::Vector2f(viewWidth, viewHeight)),
	m_gravity(0.0f, 2.f),
	m_world(m_gravity),
	m_player(std::make_unique<Player>()),
	m_map("Assets/maps/mapTest3.tmx"),
	m_contactListener(m_player.get())
{

	m_map.createCollisionBodies(m_world);
	m_player->createBody(m_world);
	m_world.SetContactListener(&m_contactListener);
	
	m_world.SetDebugDraw(&dd);
	dd.SetFlags(b2Draw::e_shapeBit);
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
	//updateDt();
	m_world.Step(timeStep, velocityIterations, positionIterations);
	m_player->update(dt);
	m_gameView.setCenter(m_player->getPosition());
	m_window.setView(m_gameView);
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
			std::cout << "KEY_PRESSED" << std::endl;
			m_player->handleInput(m_sfEvent);
		}
		
	}
}

void Game::render() 
{
	m_window.clear();
	//m_world.DrawDebugData();

	m_window.draw(m_map);

	m_window.draw(*m_player.get());

	m_window.display();
}

void Game::updateDt() {

	m_dt = m_clock.getElapsedTime().asSeconds();
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
