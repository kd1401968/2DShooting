#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
void c_PBullet::Init(Math::Vector2 Pos,int LR)
{
	m_Pos = { Pos.x,Pos.y-10 };
	m_LR = LR;
	m_Speed = { 10.0f,0.0f };
	m_Flg = true;
	m_Tex.Load("Texture/FireBullet.png");
	m_RectX = 0.0f;
}
void c_PBullet::Update()
{
	if (m_Flg) {
		if (m_LR == -1) {
			m_Pos += m_Speed;
			if (m_Pos.x >= 640) {
				m_Flg = false;
			}
		}
		else {
			m_Pos -= m_Speed;
			if (m_Pos.x <= -640) {
				m_Flg = false;
			}
		}

		m_RectX += 1.0f;
		if (m_RectX >= 45.0f) {
			m_RectX = 0.0f;
		}

		Math::Matrix S, R, T;
		S = Math::Matrix::CreateScale(m_LR*-1, 1, 1);
		T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
		m_Mat = S * T;
	}

}
void c_PBullet::Draw()
{
	Math::Rectangle Rect = { (int)m_RectX * 64,0,64,64 };
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Rect, color);
	//SHADER.m_spriteShader.DrawCircle(0, 0, 100, &color, true);
}
void c_PBullet::Release()
{
	m_Tex.Release();
}