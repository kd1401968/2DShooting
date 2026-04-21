#include "Title.h"
#include "Application/Scene.h"
#include "Application/Game/Game.h"
void c_Title::Init()
{
	m_BackTex.Load("Texture/NightForest/image.png");
}

void c_Title::Release()
{
	m_BackTex.Release();
}

void c_Title::Update()
{

	if (GetAsyncKeyState(VK_LBUTTON)&(0x8000)) {
		SCENE.ChangeScene(new c_Game());
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(0, 0, 0);
	m_BackMat = S * T;
}

void c_Title::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	Rect = { 0,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);
}
