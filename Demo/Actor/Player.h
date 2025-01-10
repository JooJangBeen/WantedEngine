#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	//Todo : RTTI ���� ���Ѿ��Ѵ�.
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(char image = 'P');

	virtual void Update(float deltaTime);
};