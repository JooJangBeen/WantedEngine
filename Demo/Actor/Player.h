#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	//Todo : RTTI 적용 시켜야한다.
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(char image = 'P');

	virtual void Update(float deltaTime);
};