#include "pch.h"
#include "DeadMobState.h"

MobStatePtr DeadMobState::handlePlayerPos(Mob& mob) { return NULL; };

void DeadMobState::update(Mob& mob) {};
void DeadMobState::enter(Mob& mob) { mob.playAnimation("die"); }
void DeadMobState::exit(Mob& mob) {};