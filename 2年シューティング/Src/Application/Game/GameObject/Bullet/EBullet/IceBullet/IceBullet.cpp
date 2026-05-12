#include "IceBullet.h"


void c_IceBullet::Init(Math::Vector2 pos, Math::Vector2 targetpos, float scale)
{
	m_Tex.Load("Texture/IcePick.png");
	m_Scale = scale*5;
	m_Pos = pos;
	m_Radius = { 32.0f * m_Scale,8.0f * m_Scale };
	m_Flg = true;

	m_Rotate = atan2f(targetpos.y - pos.y, targetpos.x - pos.x);

	float speed = 9.0f; // D‚«‚È’e‘¬

	m_Speed.x = cosf(m_Rotate) * speed;
	m_Speed.y = sinf(m_Rotate) * speed;

}
void c_IceBullet::Update()
{
	m_RectX += 0.5f;
	if (m_RectX >= 30) m_RectX = 0;

	m_Pos += m_Speed;

	if(m_Speed.x > 0)
	{
		if (m_Pos.x >= 650) m_Flg = false;
	}
	else
	{
		if (m_Pos.x <= -650) m_Flg = false;
	}
	if(m_Speed.y > 0)
	{
		if (m_Pos.y >= 350) m_Flg = false;
	}
	else
	{
		if (m_Pos.y <= -350) m_Flg = false;
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	R = Math::Matrix::CreateRotationZ(m_Rotate);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * R * T;
}

void c_IceBullet::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,0.0f,0.0f,1.0f };
	Rect = { (int)m_RectX*64,0,64,64 };
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, 0, 0, &Rect, &color);
}

void c_IceBullet::Release()
{
	m_Tex.Release();
}
