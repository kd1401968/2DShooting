#include "Start.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
void c_Start::Init()
{
	m_BackTex.Load("Texture/NightForest/Image without mist.png");
	m_Player = new c_Player;
	m_Player->Init();

	m_GameUI = new c_GameUI;
	m_GameUI->Init();

	m_BackPos = { 0.0f,0.0f };
	m_BackMoveX = 3;
}

void c_Start::Release()
{
	m_BackTex.Release();

	delete m_Player;
	delete m_GameUI;
}

void c_Start::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0);
	m_BackMat = S * T;
}

void c_Start::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	static float RectX=0;
	//RectX += m_BackMoveX;
	if (RectX <= -620) {
		RectX = 0;
	}
	Rect = { (int)RectX,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);

	m_GameUI->Draw();

	m_Player->Draw();
}
