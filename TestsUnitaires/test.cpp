#include "pch.h"
#include "../MicroProjet/Map.h"
#include "../MicroProjet/Player.h"
#include "../MicroProjet/PlayerState.h"
#include "../MicroProjet/Game.h"
#include "../MicroProjet/MobSlime.h"
#include "SFML/System/Time.hpp"

TEST(MapTest, MapBodies) {

	b2World world(b2Vec2(0, 9.8f));
	Map map("../Run/Assets/maps/mapTest4.tmx");

	EXPECT_EQ(map.getLayers().size(), 4);
	map.createBodies(world);
	int bodyCount = world.GetBodyCount();
	EXPECT_EQ(bodyCount, 22);

	b2Body* body = world.GetBodyList();
	int nbWall = 0;
	int nbActivation = 0;

	for (b2Body* body = world.GetBodyList(); body; body = body->GetNext())
	{
		EXPECT_EQ(body->GetType(), b2_staticBody);
		b2Fixture* fixture = body->GetFixtureList();
		if (fixture->GetFilterData().categoryBits == FIX_WALL)
			++nbWall;
		else if (fixture->GetFilterData().categoryBits == FIX_ACTIVATION)
			++nbActivation;


	}
	EXPECT_EQ(nbWall, 19);
	EXPECT_EQ(nbActivation, 3);
}

TEST(PlayerTest, CreatePlayer) {

	Game game; //to create models
	b2World world(b2Vec2(0, 9.8f));
	Player player;
	player.createBody(world);
	b2Body* body = world.GetBodyList();

	EXPECT_EQ(body->GetType(), b2_dynamicBody);
	int nbFixtures = 0;
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		++nbFixtures;
	}

	EXPECT_EQ(nbFixtures, 6);
	EXPECT_EQ(player.getActivationFlags(), 0x0000);


}

TEST(PlayerTest, SKillActivationJUMP)
{

	Game game("../TestsUnitaires/Assets/maps/skillActivation_1.tmx"); //to create models
	EXPECT_EQ(game.m_player->getPosition().x, 100);
	game.update();
	game.update();
	game.update();
	game.update();

	EXPECT_EQ(game.m_player->getActivationFlags(), 0x0001);

}

TEST(MobTest, MobSlimeCreate)
{
	Game game; //to create models

	b2World world(b2Vec2(0, 9.8f));
	MobSlime slime(tmx::Vector2f(0,0));

	slime.createBody(world);
	b2Body* body = world.GetBodyList();

	EXPECT_EQ(body->GetType(), b2_dynamicBody);
	int nbFixtures = 0;
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		++nbFixtures;
	}

	EXPECT_EQ(nbFixtures, 3);
	

}

TEST(MobTest, MobSlimeHit)
{
	Game game; //to create models

	b2World world(b2Vec2(0, 9.8f));
	MobSlime slime(tmx::Vector2f(0, 0));

	slime.createBody(world);

	slime.hitByPlayer(10);
	EXPECT_TRUE(!slime.dead());
	slime.hitByPlayer(10);
	EXPECT_TRUE(slime.dead());


}
