#include "PreCompiledHeader.h"
#include "Level.h"
//#include "../Actor/Actor.h"
//�Ӽ����� �߰� ���� ���丮�� �߰���
#include "Actor/Actor.h"
#include <iostream>

Level::Level()
{

}

Level::~Level()
{
	//�޸� ����
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
	//���� ��ȸ �� ���� ��û�� ���͸� ó��.
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
