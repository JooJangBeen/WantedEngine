#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(char image)
	: Super(image)
{
}

void Player::Update(float deltaTime)
{
	//Super::Update(deltaTime);

	if (Engine::Get().GetKey(VK_LEFT))
	{
		Vector2 newPosition = position;
		--newPosition.x;

		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_RIGHT))
	{
		Vector2 newPosition = position;
		++newPosition.x;

		if (newPosition.x > 40)
		{
			newPosition.x = 40;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_UP))
	{
		Vector2 newPosition = position;
		--newPosition.y;

		if (newPosition.y < 0)
		{
			newPosition.y = 0;
		}

		SetPosition(newPosition);
	}

	if (Engine::Get().GetKey(VK_DOWN))
	{
		Vector2 newPosition = position;
		++newPosition.y;

		if (newPosition.y > 25)
		{
			newPosition.y = 25;
		}

		SetPosition(newPosition);
	}
}
