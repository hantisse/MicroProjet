// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <string_view>
#include "Game.h"
#include "CollisionLayer.h"
#include "SFMLOrthogonalLayer.hpp"



using namespace std::literals::string_view_literals;

std::vector<EntityModelPtr>* GameEntityModels;


const float viewWidth = 400*1.2;
const float viewHeight = 300*1.2;

const float32 timeStep = 1.0f / 60.0f;
const int32 velocityIterations = 6;
const int32 positionIterations = 2;

Game::Game() :
	m_window(sf::VideoMode(800, 600), "MicroProjet!"),
	m_gameView(sf::Vector2f(viewHeight / 2, viewHeight / 2), sf::Vector2f(viewWidth, viewHeight)),
	m_gravity(0.0f, 0.7f),
	m_world(m_gravity),
	m_map("Assets/maps/mapTest4.tmx"),
	m_contactListener(),
	m_gameState(READY)
{

	if (!m_font.loadFromFile("Assets/fonts/pixel_font.ttf"))
	{
		std::cout << "Font could not be loaded." << std::endl;
	}
	m_playerUI = sf::Text("", m_font);
	m_playerUI.setCharacterSize(10);
	m_infoUI = sf::Text("", m_font);
	m_infoUI.setCharacterSize(20);


	createEntityModels();
	m_player = std::make_unique<Player>();

	createBodies();
	m_world.SetContactListener(&m_contactListener);
}

Game::Game(std::string mapPath) :
	m_window(sf::VideoMode(800, 600), "SFML works!"),
	m_gameView(sf::Vector2f(viewHeight / 2, viewHeight / 2), sf::Vector2f(viewWidth, viewHeight)),
	m_gravity(0.0f, 0.7f),
	m_world(m_gravity),
	m_map(mapPath),
	m_contactListener(),
	m_gameState(READY)
{
	if (!m_font.loadFromFile("Assets/fonts/pixel_font.ttf"))
	{
		std::cout << "Font could not be loaded." << std::endl;
	}

	m_playerUI = sf::Text("", m_font);
	m_playerUI.setCharacterSize(10);
	m_infoUI = sf::Text("", m_font);
	m_infoUI.setCharacterSize(20);

	createEntityModels();
	m_player = std::make_unique<Player>();

	createBodies();
	m_world.SetContactListener(&m_contactListener);
	
}

void Game::changeMap(std::string const& mapPath)
{
	m_mobs.clear();
	m_map = Map(mapPath);
	m_player = std::make_unique<Player>();
	const int nbBodies = m_world.GetBodyCount();
	for (int i = 0; i < nbBodies; ++i)
	{
		std::cout << m_world.GetBodyList() << " " << m_world.GetBodyCount() << std::endl; 
		m_world.DestroyBody(m_world.GetBodyList());
	}

	createBodies();
}

void Game::createBodies()
{
	m_map.createBodies(m_world);
	createMobBodies();
	m_player->createBody(m_world);
}


void Game::run() {
	m_gameState = RUNNING;
	while (m_window.isOpen())
	{
		pollSFMLEvent();
		update();
		render();

	}
	
}

void Game::update() {
	if (m_gameState == LOST) return;

	sf::Time dt = m_clock.restart();

	m_world.Step(timeStep, velocityIterations, positionIterations);
	m_player->update(dt);
	updateMobs(dt);

	updatePlayerUI();
	updateInfoUI();
	removeDeadObjects();

	m_gameView.setCenter(m_player->getPosition());
	m_playerUI.setPosition(m_gameView.getCenter().x - (viewWidth/2) + 20, m_gameView.getCenter().y - (viewHeight / 2) + 10);
	m_infoUI.setPosition(m_gameView.getCenter().x - 50, m_gameView.getCenter().y - 50);
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

	if (m_gameState != LOST)
	{

		m_window.draw(m_map);
		renderMobs();
		m_window.draw(*m_player.get());

		m_window.draw(m_playerUI);
	}
	m_window.draw(m_infoUI);

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

			m_mobs.push_back(std::make_unique<Mob>(FIRE_ELEMENTAL, tmx::Vector2f(
				object.getPosition().x + object.getAABB().width / 2,
				object.getPosition().y + object.getAABB().height / 2)));			
			break;
		case EntityID::SLIME:
			m_mobs.push_back(std::make_unique<Mob>(SLIME, tmx::Vector2f(
				object.getPosition().x + object.getAABB().width / 2,
				object.getPosition().y + object.getAABB().height / 2)));
			break;
		default:
			break;
		}
	}

}


void Game::removeDeadObjects()
{
	removeDeadMobs();

	for (b2Body* body : m_contactListener.toRemove)
	{
		if (body != nullptr)
		{
			m_world.DestroyBody(body);
		}
			
	}
		
	m_contactListener.toRemove.clear();
}

void Game::removeDeadMobs()
{
	std::set<b2Body*> toDestroy;

	auto mobRemove = 
	[&toDestroy] (auto& mob)
	{
			if (mob->dead() && !mob->isAnimationPlaying())
			{
				toDestroy.insert(mob->getBody());
				mob->invalidate();
			}
	};

	std::for_each(m_mobs.begin(), m_mobs.end(), mobRemove);

	m_mobs.erase(std::remove_if(m_mobs.begin(), m_mobs.end(), 
		[](auto const& mob) { return mob->dead() && !mob->isAnimationPlaying(); }), m_mobs.end());
	for (auto& mobBody : toDestroy)
	{
		m_world.DestroyBody(mobBody);
	}

}

void Game::updatePlayerUI()
{
	
	std::string s = "Unlocked : ";
	if ((m_player->getActivationFlags() & ACTIV_JUMP) == ACTIV_JUMP)
	{
		s += "Jump ";
	}
	if ((m_player->getActivationFlags() & ACTIV_SHIELD) == ACTIV_SHIELD)
	{
		s += "Block ";
	}
	if ((m_player->getActivationFlags() & ACTIV_ATTACK) == ACTIV_ATTACK)
	{
		s += "Attack ";
	}

	m_playerUI.setString(s);

}

void Game::updateInfoUI()
{
	if (m_player->dead() && m_player->isAnimationPlaying())
	{
		m_infoUI.setString("You lost");
		m_infoUI.setColor(sf::Color::Red);

		m_gameState = LOST;
	}

}

//TODO: add parsing from file
void Game::createEntityModels()
{
	EntityModels = std::vector<EntityModelPtr>(EntityID::NB_ENTITY_ID);

	std::shared_ptr<LivingEntityModel> player = std::make_shared<LivingEntityModel>("Assets/images/player/adventurer.png");
		
	player->id = EntityID::PLAYER;
	player->bodyShape.SetAsBox(5.f, 10.f);
	player->bodyFixDef.shape = &player->bodyShape;
	player->bodyFixDef.filter.categoryBits = FIX_PLAYER;
	player->spriteRect = sf::IntRect(0, 0, 50, 36);

	player->maxHealth = 50;
	player->maxVel = 7;
	player->jumpPower = 8;
	player->attackPower = 10;
	
	EntityModels[EntityID::PLAYER] = player;

	std::shared_ptr<MobModel> fire_elemental = std::make_shared<MobModel>("Assets/images/mobs/fire_elemental.png");
	
	
	fire_elemental->id = EntityID::FIRE_ELEMENTAL;
	fire_elemental->AttackBehaviourFilter = BEHAV_DIST;

	fire_elemental->bodyShape.SetAsBox(4.f, 5.f);
	fire_elemental->bodyFixDef.shape = &fire_elemental->bodyShape;
	fire_elemental->bodyFixDef.density = 15.f;
	fire_elemental->bodyFixDef.filter.categoryBits = FIX_MOB;
	fire_elemental->spriteRect = sf::IntRect(0, 0, 32, 32);

	fire_elemental->spriteOrigin = std::make_pair<int, int>(16,28);

	fire_elemental->canMove = false;
	fire_elemental->wakeDistance = 0;
	fire_elemental->attackDist = 200;
	fire_elemental->maxHealth = 20;
	fire_elemental->attackPower = 10;
	fire_elemental->attackRate = 3000;
	fire_elemental->attackTiming = 0;
	fire_elemental->jumpPower = 0;
	fire_elemental->maxVel = 0;

	thor::FrameAnimation idle, attack, die;

	idle.addFrame(1.f, sf::IntRect(0, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(32, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(64, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(96, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(128, 32, 32, 32));
	idle.addFrame(1.f, sf::IntRect(160, 32, 32, 32));


	attack.addFrame(1.f, sf::IntRect(0, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(32, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(64, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(96, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(128, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(160, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(192, 64, 32, 32));
	attack.addFrame(1.f, sf::IntRect(224, 64, 32, 32));

	die.addFrame(1.f, sf::IntRect(0, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(32, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(64, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(96, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(128, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(160, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(192, 128, 32, 32));
	die.addFrame(1.f, sf::IntRect(224, 128, 32, 32));

	fire_elemental->animator.addAnimation("idle", idle, sf::seconds(.5f));
	fire_elemental->animator.addAnimation("attack", attack, sf::seconds(.3f));
	fire_elemental->animator.addAnimation("die", die, sf::seconds(.3f));
	
	EntityModels[EntityID::FIRE_ELEMENTAL] = fire_elemental;

	std::shared_ptr<MobModel> slime = std::make_shared<MobModel>("Assets/images/mobs/slime.png");

	slime->id = EntityID::SLIME;
	slime->AttackBehaviourFilter = BEHAV_CONTACT;

	slime->bodyShape.SetAsBox(8.f, 6.f);
	slime->bodyFixDef.shape = &slime->bodyShape;
	slime->bodyFixDef.density = 15.f;
	slime->bodyFixDef.filter.categoryBits = FIX_MOB;
	slime->spriteRect = sf::IntRect(0, 0, 32, 32);

	slime->spriteOrigin = std::make_pair<int, int>(16, 20);

	slime->maxHealth = 20;
	slime->attackPower = 10;
	slime->jumpPower = 0;
	slime->wakeDistance = 150;
	slime->attackDist = 20;
	slime->attackRate = 3000;
	slime->attackTiming = 700;
	slime->canMove = true;
	slime->maxVel = 1;

	thor::FrameAnimation slimeIdle, slimeAttack, slimeDie;

	slimeIdle.addFrame(1.f, sf::IntRect(224, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(192, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(160, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(128, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(96, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(64, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(32, 0, 32, 24));
	slimeIdle.addFrame(1.f, sf::IntRect(0, 0, 32, 24));


	slimeAttack.addFrame(1.f, sf::IntRect(224, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(192, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(160, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(128, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(96, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(64, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(32, 24, 32, 25));
	slimeAttack.addFrame(1.f, sf::IntRect(0, 24, 32, 25));

	slimeDie.addFrame(1.f, sf::IntRect(224, 49, 32, 25));
	slimeDie.addFrame(1.f, sf::IntRect(192, 49, 32, 25));
	slimeDie.addFrame(1.f, sf::IntRect(160, 49, 32, 25));
	slimeDie.addFrame(1.f, sf::IntRect(96, 49, 32, 25));
	slimeDie.addFrame(1.f, sf::IntRect(64, 49, 32, 25));

	slime->animator.addAnimation("idle", slimeIdle, sf::seconds(.8f));
	slime->animator.addAnimation("attack", slimeAttack, sf::seconds(.8f));
	slime->animator.addAnimation("die", slimeDie, sf::seconds(.5f));

	EntityModels[EntityID::SLIME] = slime;

	std::shared_ptr<EntityModel> projectile = std::make_shared<EntityModel>("Assets/images/mobs/fire_projectile.png");

	projectile->id = EntityID::FIRE_PROJECTILE;
	projectile->bodyShape.SetAsBox(3.f, 3.f);
	projectile->bodyFixDef.shape = &projectile->bodyShape;

	projectile->bodyFixDef.density = 0;
	projectile->bodyFixDef.filter.categoryBits = FIX_BULLET;
	projectile->bodyFixDef.filter.maskBits = FIX_PLAYER | FIX_WALL | FIX_SHIELD;
	projectile->bodyFixDef.isSensor = true;
	projectile->spriteRect = sf::IntRect(0, 0, 3, 3);

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
