#include "Ghost.h"
void c_Ghost::Init(Math::Vector2 Pos)
{
	m_Tex.Load("Texture/MiniGhost_Idle.png");
	m_Pos = Pos;
	m_Flg = true;
	m_RectX = 0.0f;
	m_Scale = { 2.0f,2.0f };
	m_Radius = { 32.0f*m_Scale.x,32.0f*m_Scale.y };
	m_Alpha = 1.0f;
	if (Pos.x > 0) 
	{
		m_LR = 1;
		m_Speed = { 6.0f,0.0f };
	}
	else 
	{
		m_LR = -1;
		m_Speed = { -6.0f,0.0f };
	}
}
void c_Ghost::Update()
{
	if (!m_Flg)return;

	m_RectX += 0.5f;
	if (m_RectX >= 9.0f)
	{
		m_RectX = 0.0f;
	}

	m_Pos.x -= m_Speed.x;
	if (m_LR == 1)
	{
		if (m_Pos.x <= -740 - m_Radius.x)m_Flg = false;
	}
	else
	{
		if (m_Pos.x >= +740 + m_Radius.x)m_Flg = false;
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_LR*m_Scale.x, m_Scale.y, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;
}
void c_Ghost::Draw()
{
	Math::Rectangle rect = { 32 * (int)m_RectX,0,32,32 };
	Math::Color color = { 1.0f,1.0f,1.0f,m_Alpha };
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, rect, color);
	//SHADER.m_spriteShader.DrawBox(0, 0, 119, 100, &color, true);
}
void c_Ghost::Release()
{
	m_Tex.Release();
}

//void c_Ghost::AbsSetFlg(bool Flg)
//{
//	m_Alpha -= 0.05f;
//	if(m_Alpha <= 0.0f)
//	{
//		m_Alpha = 0.0f;
//		m_Flg = Flg;
//	}
//}