#pragma once

#include"Core.h"
#include "Container/List.h"
#include "RTTI.h"

//���� ����
class Actor;

class ENGINE_API Level : public RTTI
{
	//RTTI����
	RTTI_DECLARATIONS(Level, RTTI)
public:
	Level();
	virtual ~Level();

	//���� �߰� �Լ�
	void AddActor(Actor* newActor);

	//���� ��û�� �� ���͸� �����ϴ� �Լ�.
	void DestroyActor();

	virtual void Update(float deltaTime);
	virtual void Draw();

protected:

	//���� ������ ��ġ�Ǵ� ��ü(����) �迭
	List<Actor*> actors;

	////������ �� �ִ� ������ ũ��
	//int capacity;

	////������ ��
	//int actorCount = 0;
};

