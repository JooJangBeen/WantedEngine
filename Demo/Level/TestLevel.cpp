#include "TestLevel.h"
#include "Engine/Engine.h"
#include "../Actor/Player.h"

TestLevel::TestLevel()
{
	AddActor(new Player('A'));
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}
}
