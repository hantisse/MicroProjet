#include "pch.h"
#include "Mob.h"
#include <iostream>
#include "MobState.h"
#include "HitMobState.h"
#include "SleepingMobState.h"
#include "MobDistanceAttackBehaviour.h"
#include "MobContactAttackBehaviour.h"

int distanceToUpdate = 400;

Mob::Mob(EntityID id, tmx::Vector2f position) :
	LivingEntity(id)
	
{
	m_bodyDef.type = b2_dynamicBody;

	m_bodyDef.position.Set(position.x, position.y);
	m_bodyData = { true, FIX_MOB, getModel()->attackPower, this };
	
	m_lifeBar.setFillColor(sf::Color::Red);
	m_lifeBar.setOrigin(20, 0);
	m_life.setFillColor(sf::Color::Green);

	const MobModel* model = getModel();

	std::cout << id << " " << model->spriteOrigin.first << " " << model->spriteOrigin.second << std::endl;
	m_sprite.setOrigin(model->spriteOrigin.first, model->spriteOrigin.second);
	m_state = std::make_unique<SleepingMobState>();

	loadAnimations();
	initBehaviours();
}

Mob::~Mob()
{
}

void Mob::update(sf::Time dt)
{
	if (m_distanceToPlayer > distanceToUpdate)
		return;
	Entity::update(dt);
	handlePlayerPos();
	m_state->update(*this);
	m_lifeBar.setPosition(m_body->GetPosition().x, m_body->GetPosition().y - 20);
	m_life.setScale(std::max(0.,static_cast<double>(m_health) / getModel()->maxHealth), 1);
	m_life.setPosition(m_body->GetPosition().x - m_lifeBar.getGlobalBounds().width/2, m_body->GetPosition().y - 20);

	for (auto const& behaviour : m_attackBehaviours)
	{
		behaviour->update(dt);
	}
}

void Mob::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_distanceToPlayer > distanceToUpdate)
		return;
	LivingEntity::draw(target, states);

	for (auto const& behaviour : m_attackBehaviours)
	{
		behaviour->draw(target, states);
	}
}

void Mob::createBody(b2World& world)
{
	Entity::createBody(world);
	for (auto& behaviourPtr : m_attackBehaviours)
	{
		behaviourPtr->createBody(*this);
	}
}

void Mob::handlePlayerPos()
{
	for (auto const& behaviourPtr : m_attackBehaviours)
	{
		if (behaviourPtr->isActive(*this))
		{
			m_currentBehaviour = behaviourPtr.get();
			activeAttackBox(false);
			break;
		}
		m_currentBehaviour = nullptr;
	}

	MobStatePtr newState = m_state->handlePlayerPos(*this);
	if (newState != nullptr)
	{
		m_state = std::move(newState);
		m_state->enter(*this);
	}
}

void Mob::activeAttackBox(bool active)
{
	m_currentBehaviour->activeAttackBox(*this, active);
}

b2Body* Mob::getBody() const
{
	return m_body; 
}



void Mob::takeDamage(int damage)
{
	m_health -= damage;
	m_state = std::make_unique<HitMobState>();
	m_state->enter(*this);
	
}

void Mob::updateDistToPlayer(sf::Vector2f playerPos)
{

	m_distanceToPlayer = std::sqrt((std::pow(m_body->GetPosition().x - playerPos.x, 2) + std::pow(m_body->GetPosition().y - playerPos.y, 2)));
	setDirection((m_body->GetPosition().x - playerPos.x) < 0 ? Direction::RIGHT : Direction::LEFT);

}

void Mob::attack() const
{
	m_currentBehaviour->attack(*this);
}

MobAttackVect const& Mob::getAttackBehaviours() const
{
	return m_attackBehaviours;
}

void Mob::setCurrentAttackBehaviour(MobAttackBehaviour* behaviour)
{
	m_currentBehaviour = behaviour;
}

bool Mob::canAttack() const
{ 
	return m_currentBehaviour != nullptr; 
}

bool Mob::canMove() const
{ 
	return getModel()->canMove; 
}
bool Mob::awake() const
{ 
	return m_distanceToPlayer < getModel()->wakeDistance; 
}
int Mob::getAttackRate() const
{
	//return getModel()->attackRate;
	return m_currentBehaviour->getAttackRate();
}
int Mob::getAttackTiming() const
{ 
	//return getModel()->attackTiming; 
	return m_currentBehaviour->getAttackTiming();
}

bool compare_by_uniqptr(const std::unique_ptr<MobAttackBehaviour>& a,
	const std::unique_ptr<MobAttackBehaviour>& b) 
{
	return *a.get() < *b.get();
}

void Mob::addAttackBehaviour(std::unique_ptr<MobAttackBehaviour> behaviourPtr)
{
	m_attackBehaviours.push_back(std::move(behaviourPtr));
	std::sort(m_attackBehaviours.begin(), m_attackBehaviours.end(), compare_by_uniqptr);

}


MobModel const* Mob::getModel() const
{
	assert(m_model->type == MOD_MOB);
	return static_cast<MobModel*>(m_model.get());
}


void Mob::loadAnimations()
{
	m_animator = getModel()->animator;
}

void Mob::initBehaviours()
{
	const MobModel* model = getModel();
	unsigned short filter = getModel()->AttackBehaviourFilter;

	if ((filter & BEHAV_CONTACT) == BEHAV_CONTACT)
	{
		addAttackBehaviour(std::make_unique<MobContactAttackBehaviour>(model->attackDist, model->attackPower, model->attackRate, model->attackTiming));
	}

	if ((filter & BEHAV_DIST) == BEHAV_DIST)
	{
		addAttackBehaviour(std::make_unique<MobDistanceAttackBehaviour>(model->attackDist, model->attackPower, model->attackRate, model->attackTiming));
	}

	
}