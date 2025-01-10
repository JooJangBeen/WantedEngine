#include "PreCompiledHeader.h"
#include "Level.h"
//#include "../Actor/Actor.h"
//속성에서 추가 포함 디렉토리에 추가시
#include "Actor/Actor.h"
#include <iostream>

Level::Level()
{

}

Level::~Level()
{
	//메모리 해제
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	actors.PushBack(newActor);
}

void Level::DestroyActor()
{
	//액터 순회 후 삭제 요청된 액터를 처리.
	for (int i = 0; i < actors.Size();)
	{
		if (actors[i]->isExpired)
		{
			delete actors[i];
			actors[i] = nullptr;
			actors.Erase(i);
			continue;
		}

		++i;
	}
}

void Level::Update(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (!actor->IsActive() || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	for (Actor* actor : actors)
	{
		if (!actor->IsActive() || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}
