#include "BigGhost.h"
void c_BigGhost::Init(Math::Vector2 Pos)
{
	m_Tex.Load("Texture/MiniGhost_Idle.png");
	m_Scale =27.0f;
	m_StartPos = Pos;
	m_Pos = m_StartPos;
	m_RectX = 0.0f;
	m_Flg = true;
	m_Move = true;
	m_Radius = { 30.0f*5 ,720  };
	if(Pos.x > 0)
	{
		m_LR = 1;
		m_Speed = 15.0f;
	}
	else
	{
		m_LR = -1;
		m_Speed = -15.0f;
	}
}

void c_BigGhost::Update()
{
	if (m_Move == true)
	{
		if (m_LR == -1)
		{
			if (m_Pos.x <= -740)
			{
				m_Pos.x -= m_Speed/3;
			}
			else 
			{
				m_Move = false;
			}
		}
		else 
		{
			if (m_Pos.x >= 740)
			{
				m_Pos.x -= m_Speed/3;
			}
			else
			{
				m_Move = false;
			}
		}
	}

	m_RectX += 0.3f;
	if (m_RectX >= 9.0f)
	{
		m_RectX = 0.0f;
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale*m_LR,m_Scale,1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;
}

void c_BigGhost::Draw()
{
	Math::Rectangle rect = { 32 * (int)m_RectX,0,32,32 };
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, rect, color);
}

void c_BigGhost::GoGhost()
{
	m_Pos.x -= m_Speed*1.8f;
}

void c_BigGhost::BackGhost()
{
	m_Pos.x += m_Speed*2.0f;
	if (m_LR == 1)
	{
		if (m_Pos.x > m_StartPos.x)
		{
			m_Pos.x = m_StartPos.x;
		}
	}
	else
	{
		if (m_Pos.x < m_StartPos.x)
		{
			m_Pos.x = m_StartPos.x;
		}
	}
}

void c_BigGhost::EndFlg()
{
	Math::Vector2 dir = { m_StartPos.x - m_Pos.x, m_StartPos.y - m_Pos.y };
	float invLen = 1.0f / sqrtf(dir.x * dir.x + dir.y * dir.y);

	dir.x *= invLen;
	dir.y *= invLen;

	m_Pos.x -= dir.x * m_Speed/7;
	m_Pos.y -= dir.y * m_Speed/7;

	if(m_StartPos==m_Pos)
	{
		m_Flg = false;
	}

}

void c_BigGhost::Release()
{
	m_Tex.Release();
}
