#pragma once
#include "LivingEntity.h"
#include <tmxlite/Types.hpp>
#include <stack>
#include <string>
#include "MobAttackBehaviour.h"

class MobState;
typedef std::unique_ptr<MobState> MobStatePtr;
typedef std::vector<std::unique_ptr<MobAttackBehaviour>> MobAttackVect;


class Mob : public LivingEntity
{
	friend class MobAttackBehaviour;

public:
	Mob(EntityID id, tmx::Vector2f position);
	~Mob();
	void update(sf::Time dt) override;
	void updateDistToPlayer(sf::Vector2f playerPos);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void createBody(b2World& world) override;

	b2Body* getBody() const;

	void activeAttackBox(bool active);


	//returns the sorted (by activation distance) vector of attack behaviours
	MobAttackVect const& getAttackBehaviours() const;
	void setCurrentAttackBehaviour(MobAttackBehaviour* behaviour);


	void attack() const;

	bool canAttack() const; 
	bool canMove() const;
	bool awake() const;
	int getAttackRate() const;
	int getAttackTiming() const;
	void takeDamage(int damage) override;

	MobModel const* getModel() const;
private:

	MobStatePtr m_state;
	MobAttackBehaviour* m_currentBehaviour;

	//Updated during each loop
	int m_distanceToPlayer;

	void handlePlayerPos();

	//sorted vector of attack behaviours. Use addAttackBehaviour to add behaviours
	MobAttackVect m_attackBehaviours;

	void loadAnimations();
	void initBehaviours();

	//adds behaviour to the vector of attack behaviours. Keeps the vector sorted
	void addAttackBehaviour(std::unique_ptr<MobAttackBehaviour> behaviour);
};

