#pragma once

#include"Core.h"
#include "Math/Vector2.h"

struct KeyState
{
	//���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool isKeyDown = false;

	//���� �����ӿ� Ű�� ���Ⱦ����� Ȯ��
	bool wasKeyDown = false;
};

enum class CursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor,
};

class Level;
class Actor;
class ENGINE_API Engine
{
public:
	Engine();
	virtual ~Engine();

	void Run();

	//���� �߰� �Լ�
	void LoadLevel(Level* newLevel);

	//���� �߰�, ���� �Լ�.
	void AddActor(Actor* newActor);
	void DestroyActor(Actor* targetActor);

	//ȭ�� ��ǥ ���� �Լ�.
	void SetCursorType(CursorType cursortype);
	void SetCursorPosition(const Vector2& position);
	void SetCursorPosition(int x, int y);

	//Ÿ�� ������ �ӵ� ���� �Լ�.
	void SetTargetGrameRate(float targetFrameRate);

	//�Է� ���� �Լ�
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	//���� ���� �Լ�
	void QuitGame();

	//�̱��� ��ü ���� �Լ�
	static Engine& Get();


protected:
	void ProcessInput();
	void Update(float deltaTime);
	void Clear();
	void Draw();

	//���� �������� Ű ���¸� �����ϴ� �Լ�
	void SavePreviousKeyStates();

protected:
	//Ÿ�� ������ ����
	float targetFrameRate = 60.0f;
	//�� ������ �ð�(���� : ��).
	float targetOneFrameTime = 0.0f;

	bool quit;

	//Ű ���¸� ���� �ϴ� �迭
	KeyState keyState[255];

	//�̱��� ������ ���� ���� ���� ����.
	static Engine* instance;

	//���� ���� ����
	Level* mainLevel;

	//�������� ������Ʈ�ؾ� �ϴ��� ���θ� ��Ÿ���� ����.
	bool shouldUpdate = true;

};