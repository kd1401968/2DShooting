#include "Explosion.h"
void c_Explosion::Init(Math::Vector2 Pos,float Scale)
{
	m_Flg = true;
	m_Pos = Pos;
	m_Scale = Scale;
	m_Tex.Load("Texture/Explosion.png");
	m_Anime = 0.0f;
}
void c_Explosion::Update()
{
	m_Anime += 1.0f;
	if (m_Anime >= 44)
	{
		m_Flg = false;
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y+12, 0);
	m_Mat = S * T;
}
void c_Explosion::Draw()
{
	Math::Rectangle rect = { 96*(int)m_Anime,0,96,96};
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, 0, 0, &rect, &color);
}
void c_Explosion::Release()
{
	m_Tex.Release();
}