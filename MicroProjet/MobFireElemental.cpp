#include "pch.h"
#include "MobFireElemental.h"
#include "SleepingMobState.h"
#include <iostream>
#include "Projectile.h"

MobFireElemental::MobFireElemental(tmx::Vector2f position) :
	Mob("Assets/images/mobs/fire_elemental.png", 150, position)
{

	m_maxHealth = 20;
	m_health = m_maxHealth;
	m_attackPower = 10;
	m_attackRate = 3000;

	m_bodyDef.type = b2_dynamicBody;

	m_bodyShape.SetAsBox(4.f, 5.f);

	m_bodyFixDef.shape = &m_bodyShape;
	m_bodyFixDef.density = 15.f;
	m_bodyFixDef.filter.categoryBits = FixtureType::MOB;
	

	m_spriteRect = sf::IntRect(0, 0, 32, 32);

	m_sprite = sf::Sprite(m_sourceTexture, m_spriteRect);
	m_sprite.setOrigin(16, 28);

	loadAnimations();

	m_state = std::make_unique<SleepingMobState>();
}

void MobFireElemental::loadAnimations()
{
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

	m_animator.addAnimation("idle", idle, sf::seconds(.5f));
	m_animator.addAnimation("attack", attack, sf::seconds(.3f));
	m_animator.addAnimation("die", die, sf::seconds(.3f));
}

void MobFireElemental::attack()
{
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>();
	projectile->m_projectileDef.bodyDef.position.Set(m_body->GetPosition().x, m_body->GetPosition().y - 5);
	projectile->m_body = m_body->GetWorld()->CreateBody(&projectile->m_projectileDef.bodyDef);

	projectile->m_projectileDef.fixtureDef.filter.categoryBits = FixtureType::BULLET;
	projectile->m_projectileDef.fixtureDef.filter.maskBits = ~(FixtureType::MOB | FixtureType::SWORD);
	projectile->m_projectileDef.fixtureDef.isSensor = true;

	projectile->m_projectileDef.data = { true, FixtureType::BULLET, &projectile->m_projectileDef.damage, projectile->m_body };
	projectile->m_projectileDef.fixtureDef.userData = &projectile->m_projectileDef.data;

	projectile->m_body->CreateFixture(&projectile->m_projectileDef.fixtureDef);
	projectile->m_body->SetGravityScale(0);

	float vel = m_direction == RIGHT ? 5. : -5.;
	projectile->m_body->SetLinearVelocity(b2Vec2(vel,0));

	std::cout << "Creation : " << projectile->m_body << std::endl;

	m_projectiles.push_back(std::move(projectile));

}

void MobFireElemental::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Mob::draw(target, states);
	for (auto const& proj : m_projectiles)
		proj->draw(target, states);
}

void MobFireElemental::update(sf::Time dt)
{
	Mob::update(dt);
	for (auto const& proj : m_projectiles)
		proj->update();
}

void MobFireElemental::createAttackHitBoxes(b2World& world)
{
	
}