#include "Stage2.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
void c_Stage2::Init(int PlayerLife)
{
	m_StartPos = { -800.0f,0.0f };

	m_BackTex.Load("Texture/NightForest/Image without mist.png");
	m_Player = new c_Player(PlayerLife, m_StartPos);

	m_GameUI = new c_GameUI(PlayerLife);

	m_BackPos = { 0.0f,0.0f };

}
void c_Stage2::Release()
{
	m_BackTex.Release();

	delete m_Player;
	delete m_GameUI;
}
void c_Stage2::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0);
	m_BackMat = S * T;
}

void c_Stage2::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	Rect = { 0,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);

	m_GameUI->Draw();

	m_Player->Draw();
}
