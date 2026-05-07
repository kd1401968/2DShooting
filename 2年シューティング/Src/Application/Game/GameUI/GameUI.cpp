#include "Application/Game/GameUI/GameUI.h"
void c_GameUI::Init() 
{
	m_LifeTex.Load("Texture/Life.png");
	for(int i=0;i<LIFE_MAX;i++)
	{
		m_LifeMat[i] = Math::Matrix::Identity;
		m_LifeFlg[i] = true;
		m_LifePos[i] = { -580.0f + i * 80.0f, -320.0f };
	}
	m_LifeScale = 0.25f;
}
void c_GameUI::Update(int i)
{
	// Œ»Ý‚Ìƒ‰ƒCƒt”‚ð”‚¦‚é
	int life = 0;
	for (int j = 0; j < LIFE_MAX; j++) {
		if (m_LifeFlg[j]) life++;
	}

	// Œ¸‚Á‚Ä‚¢‚½‚ç false ‚É‚·‚é
	for (int j = i; j < LIFE_MAX; j++) {
		m_LifeFlg[j] = false;
	}



	for (int j = 0; j < LIFE_MAX; j++) {
		Math::Matrix S, R, T;
		S = Math::Matrix::CreateScale(m_LifeScale);
		T = Math::Matrix::CreateTranslation(m_LifePos[j].x, m_LifePos[j].y, 0.0f);
		m_LifeMat[j] = S * T;
	}
}
void c_GameUI::Draw()
{
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -320, 640, 40, &color, true);


	Math::Rectangle rect = { 0,0,457,393 };
	for (int i = 0; i < LIFE_MAX; i++) {
		if (m_LifeFlg[i]) {
			color = { 1.0f,1.0f,1.0f,1.0f };
		}
		else {
			color = { 0.1f,0.1f,0.1f,0.5f };
		}
		SHADER.m_spriteShader.SetMatrix(m_LifeMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_LifeTex, rect, color);
	}
	
}
void c_GameUI::Release()
{
	m_LifeTex.Release();
}