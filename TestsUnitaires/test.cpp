#include "pch.h"
#include "../MicroProjet/Map.h"
#include "../MicroProjet/Player.h"
#include "../MicroProjet/PlayerState.h"
#include "../MicroProjet/Game.h"
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
	EXPECT_EQ(player.getJumpPower(), 8);
	EXPECT_EQ(player.getMaxVel(), 7);
	EXPECT_EQ(nbFixtures, 6);
	EXPECT_EQ(player.getActivationFlags(), 0x0000);


}

TEST(PlayerTest, SKillActivation)
{

	Game game("../TestsUnitaires/Assets/maps/skillActivation_1.tmx");
	game.update();
	EXPECT_EQ(game.m_player->getActivationFlags(), 0x0001);

	game.changeMap("../TestsUnitaires/Assets/maps/skillActivation_2.tmx");
	game.update();
	EXPECT_EQ(game.m_player->getActivationFlags(), 0x0002);

	game.changeMap("../TestsUnitaires/Assets/maps/skillActivation_3.tmx");
	game.update();
	EXPECT_EQ(game.m_player->getActivationFlags(), 0x0004);

}

TEST(MobTest, ContactMobCreate)
{
	Game game; //to create models

	b2World world(b2Vec2(0, 9.8f));
	Mob slime(SLIME,tmx::Vector2f(0,0));

	slime.createBody(world);
	b2Body* body = world.GetBodyList();

	EXPECT_EQ(body->GetType(), b2_dynamicBody);
	int nbFixtures = 0;
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		++nbFixtures;
	}

	EXPECT_EQ(nbFixtures, 3);

	EXPECT_EQ(slime.getJumpPower(), 0);
	EXPECT_EQ(slime.getMaxVel(), 1);
	EXPECT_EQ(slime.getAttackBehaviours()[0]->getAttackRate(), 3000);
	EXPECT_EQ(slime.getAttackBehaviours()[0]->getAttackTiming(), 700);
	EXPECT_EQ(slime.canMove(), true);

}

TEST(MobTest, DistanceMobCreate)
{
	Game game; //to create models

	b2World world(b2Vec2(0, 9.8f));
	Mob fireElem(FIRE_ELEMENTAL, tmx::Vector2f(0, 0));

	fireElem.createBody(world);
	b2Body* body = world.GetBodyList();

	EXPECT_EQ(body->GetType(), b2_dynamicBody);
	int nbFixtures = 0;
	for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		++nbFixtures;
	}

	EXPECT_EQ(nbFixtures, 1);

	EXPECT_EQ(fireElem.getJumpPower(), 0);
	EXPECT_EQ(fireElem.getMaxVel(), 0);
	EXPECT_EQ(fireElem.getAttackBehaviours()[0]->getAttackRate(), 3000);
	EXPECT_EQ(fireElem.getAttackBehaviours()[0]->getAttackTiming(), 0);
	EXPECT_EQ(fireElem.canMove(), false);

}

TEST(MobTest, DistanceMobAttack)
{

	Game game; //to create models
	b2World world(b2Vec2(0, 9.8f));
	Mob fireElem(FIRE_ELEMENTAL,tmx::Vector2f(0, 0));
	fireElem.createBody(world);
	fireElem.setCurrentAttackBehaviour(fireElem.getAttackBehaviours()[0].get());


	EXPECT_EQ(world.GetBodyCount(), 1);
	fireElem.attack();
	EXPECT_EQ(world.GetBodyCount(), 2);
	int nbFixtures = 0;
	b2Body* projectile = world.GetBodyList();
	EXPECT_EQ(projectile->GetGravityScale(), 0);


	EXPECT_EQ(projectile->GetType(), b2_dynamicBody);
	EXPECT_EQ(projectile->GetPosition().x, world.GetBodyList()->GetPosition().x);
	   
	for (b2Fixture* fixture = projectile->GetFixtureList(); fixture; fixture = fixture->GetNext())
	{
		++nbFixtures;
	}
	EXPECT_EQ(nbFixtures, 1);

	b2Fixture* fixture = projectile->GetFixtureList();
	EXPECT_TRUE(fixture->IsSensor());
	FixtureContactData* data = static_cast<FixtureContactData*>(fixture->GetUserData());
	EXPECT_TRUE(data->type, FIX_BULLET);
	EXPECT_TRUE(data->data, 10);


}

TEST(GameTest, MobRemoval)
{

	Game game("../MicroProjet/Assets/maps/mapTest3.tmx"); //to create models
	game.m_gameState = RUNNING;
	EXPECT_EQ(game.m_mobs.size(), 2);

	int worldBodyCount = game.m_world.GetBodyCount();
	
	game.m_mobs[0]->takeDamage(20);
	game.m_mobs[1]->takeDamage(20);
	EXPECT_TRUE(game.m_mobs[0]->dead());
	EXPECT_TRUE(game.m_mobs[1]->dead());
	EXPECT_TRUE(!game.m_mobs[1]->isAnimationPlaying());
	EXPECT_TRUE(!game.m_mobs[1]->isAnimationPlaying());

	game.update();

	while(!game.m_mobs.empty() && game.m_mobs[0]->isAnimationPlaying())
	{
		game.update();
	}
	while (!game.m_mobs.empty() && game.m_mobs[1]->isAnimationPlaying())
	{
		game.update();
	}
	
	
	
	EXPECT_EQ(game.m_world.GetBodyCount(), worldBodyCount - 2);
	EXPECT_TRUE(game.m_mobs.empty());
	
}


TEST(LivingEntityTest, TakeDamage)
{
	Game game; //to create models

	b2World world(b2Vec2(0, 9.8f));
	Mob slime(SLIME, tmx::Vector2f(0, 0));
	Player player;
	
	slime.createBody(world);
	player.createBody(world);

	slime.takeDamage(10);
	EXPECT_TRUE(!slime.dead());
	slime.takeDamage(10);
	EXPECT_TRUE(slime.dead());

	player.takeDamage(10);
	EXPECT_TRUE(!player.dead());
	player.takeDamage(40);
	EXPECT_TRUE(player.dead());

}
