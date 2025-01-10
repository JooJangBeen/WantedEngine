#include "PreCompiledHeader.h"
#include "Engine.h"
#include <Windows.h>
#include <iostream>
#include "Level/Level.h"
#include "Actor/Actor.h"

//스태틱 변수 초기화
Engine* Engine::instance = nullptr;

Engine::Engine()
	: quit(false), mainLevel(nullptr)
{
	//싱글톤 객체를 설정
	instance = this;

	//기본 타겟 프레임 속도 설정.
	SetTargetGrameRate(60.0f);
}

Engine::~Engine()
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
	}
}

void Engine::Run()
{
	//unsigned long currentTime = timeGetTime();;
	//unsigned long previousTime = 0;

	//CPU 시계 사용
	//시스템 시계-> 고해상도 카운터.
	//메인보드에 시계가 있음.
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	//std::cout << "Frequency : " << frequency.QuadPart << std::endl;

	//시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);

	int64_t currentTime = time.QuadPart;
	int64_t previousTime = 0;

	//프레임 제한
	//float targetFrameRate = 60.0f;

	//한프레임에 걸리는 시간
	//float targetOneFrameTime = 1.0f / targetFrameRate;

	while (true)
	{
		if (quit)
		{
			break;
		}

		QueryPerformanceCounter(&time);
		currentTime = time.QuadPart;

		//프레임 시간 계산
		float deltaTime = static_cast<float>(currentTime - previousTime) /
			static_cast<float>(frequency.QuadPart);


		//프레임 확인
		if (deltaTime >= targetOneFrameTime)
		{
			//입력 처리(현재 키의 눌림 상태 확인)
			ProcessInput();

			//업데이트 가능한 상태에서만 프레임 업데이트 처리.
			if (shouldUpdate)
			{
				Update(deltaTime);
				Draw();
			}

			//키상태 저장
			SavePreviousKeyStates();

			previousTime = currentTime;

			//액터 정리(삭제 요청된 액터들 정리).
			if (mainLevel != nullptr)
			{
				mainLevel->DestroyActor();
			}

			//프레임 활성화
			shouldUpdate = true;
		}
	}
}

void Engine::LoadLevel(Level* newLevel)
{
	if (mainLevel != nullptr)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	//메인레벨 설정
	mainLevel = newLevel;


}

void Engine::AddActor(Actor* newActor)
{
	//예외처리
	if (mainLevel == nullptr) return;

	shouldUpdate = false;
	mainLevel->AddActor(newActor);
}

void Engine::DestroyActor(Actor* targetActor)
{
	//예외처리
	if (mainLevel == nullptr) return;

	shouldUpdate = false;
	targetActor->Destroy();
}

void Engine::SetCursorType(CursorType cursorType)
{
	//1.커서 속성 구조체 설정.
	CONSOLE_CURSOR_INFO info = { };

	//타입 별로 구조체 값 설정.
	switch (cursorType)
	{
		case CursorType::NoCursor:
		{
			info.dwSize = 1;
			info.bVisible = FALSE;
			break;
		}
		case CursorType::SolidCursor:
		{
			info.dwSize = 100;
			info.bVisible = TRUE;
			break;
		}
		case CursorType::NormalCursor:
		{
			info.dwSize = 20;
			info.bVisible = TRUE;
			break;
		}
	}

	//2. 설정
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void Engine::SetCursorPosition(const Vector2& position)
{
	SetCursorPosition(position.x, position.y);
}

void Engine::SetCursorPosition(int x, int y)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(handle, coord);
}

void Engine::SetTargetGrameRate(float targetFrameRate)
{
	this->targetFrameRate = targetFrameRate;
	targetOneFrameTime = 1.0f / targetFrameRate;
}

bool Engine::GetKey(int key)
{
	return keyState[key].isKeyDown;
}

bool Engine::GetKeyDown(int key)
{
	return keyState[key].isKeyDown && !keyState[key].wasKeyDown;
}

bool Engine::GetKeyUp(int key)
{
	return !keyState[key].isKeyDown && keyState[key].wasKeyDown;
}

void Engine::QuitGame()
{
	quit = true;
}

Engine& Engine::Get()
{
	return *instance;
}

void Engine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].isKeyDown = (GetAsyncKeyState(i) & 0x8000) ? true : false;
	}
}

void Engine::Update(float deltaTime)
{
	//ESC키로 게임 종료.
	//if (GetKeyDown(VK_ESCAPE))
	//{
	//	QuitGame();
	//}

	if (mainLevel != nullptr)
	{
		//레벨 업데이트
		mainLevel->Update(deltaTime);
	}

	//std::cout << "DeltaTime : " << deltaTime << ", FPS : " << (1.0f / deltaTime) << "\n";
}

void Engine::Clear()
{
	//화면의 (0,0)으로 이동.
	SetCursorPosition(0, 0);

	int height = 30;
	for (int i = 0; i < height; ++i)
	{
		Log("                              \n");
	}

	//화면의 (0,0)으로 이동.
	SetCursorPosition(0, 0);
}

void Engine::Draw()
{
	//화면 지우기.
	Clear();

	if (mainLevel != nullptr)
	{
		//레벨 Draw
		mainLevel->Draw();
	}
}

void Engine::SavePreviousKeyStates()
{
	for (int i = 0; i < 255; ++i)
	{
		keyState[i].wasKeyDown = keyState[i].isKeyDown;
	}
}
