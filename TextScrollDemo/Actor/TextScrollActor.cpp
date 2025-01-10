#include "TextScrollActor.h"
#include "Engine/Engine.h"
TextScrollActor::TextScrollActor(const char* message)
{
	length = (int)strlen(message);

	string = new char[length + 1];
	strcpy_s(string, length + 1, message);

	Engine::Get().SetCursorType(CursorType::NoCursor);
}

TextScrollActor::~TextScrollActor()
{
	delete[] string;
}

void TextScrollActor::Update(float deltaTime)
{
	//ESC 종료.
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	elapsedTime += deltaTime;
	if (elapsedTime < delayTime)
	{
		return;
	}

	elapsedTime = 0.0f;
	//화면에 그릴 문자열의 시작 인덱스 업데이트.
	index = (index + 1) % length;
}

void TextScrollActor::Draw()
{
	// 임시 문자열 버퍼.
	char* temp = new char[printWidth + 1];
	int tempIndex = index;

	for (int ix = 0; ix < printWidth; ++ix)
	{
		temp[ix] = string[tempIndex];
		tempIndex = (tempIndex + 1) % length;
	}

	temp[printWidth] = '\0';
	Log(temp);

	delete[] temp;
	Engine::Get().SetCursorPosition(0, 0);
}
