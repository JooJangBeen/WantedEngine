#include "PreCompiledHeader.h"
#include "DrawableActor.h"
#include "Engine/Engine.h"

DrawableActor::DrawableActor(const char* image)
	: Actor()/*, image(image)*/
{
	// 전달 받은 문자열 복사.
	auto length = strlen(image) + 1;
	this->image = new char[length];
	strcpy_s(this->image, length, image);
}

DrawableActor::~DrawableActor()
{
	delete[] image;
}

void DrawableActor::Draw()
{
	Super::Draw();

	//그리기.
	//1단계: 콘솔 자표 옮기기.
	Engine::Get().SetCursorPosition(position);

	//2단계 그리기(콘솔 출력).
	Log("%c", image);

}

void DrawableActor::SetPosition(const Vector2& newPosition)
{
	//위치 먼저 지우기
	Engine::Get().SetCursorPosition(position);
	Log(" ");

	Super::SetPosition(newPosition);
}
