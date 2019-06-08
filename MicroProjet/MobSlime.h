#pragma once
#include "ContactMob.h"

class MobSlime : public ContactMob
{
public:
	MobSlime(tmx::Vector2f position);
private:
	void loadAnimations() override;
	
};

