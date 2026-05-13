#include "Star.h"

void c_Star::Update()
{
	m_RectX += 0.5f;
	if (m_RectX >= 60)
	{
		m_RectX = 0;
	}

	if (m_Speed.x > 0)
	{
		if (m_Pos.x >= 650) m_Flg = false;
	}
	else
	{
		if (m_Pos.x <= -650) m_Flg = false;
	}
	if (m_Speed.y > 0)
	{
		if (m_Pos.y >= 400) m_Flg = false;
	}
	else
	{
		if (m_Pos.y <= -350) m_Flg = false;
	}

	m_Conut++;
	if (m_Conut >= 60&&m_Conut<=79)
	{
		m_Speed = { 0,0 };
	}
	if (m_Conut == 80)
	{
		// 方向ベクトル（ターゲット - 自分）
		Math::Vector2 dir = {
			m_TGPos.x - m_Pos.x,
			m_TGPos.y - m_Pos.y
		};

		// 正規化（長さ1にする）
		float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
		if (len != 0)
		{
			dir.x /= len;
			dir.y /= len;
		}

		float speed = 8.0f;

		// 速度ベクトルを保存（これが固定される）
		m_Speed.x = dir.x * speed;
		m_Speed.y = dir.y * speed;


	}


	m_Pos += m_Speed;

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;
}

void c_Star::Draw()
{
	Math::Rectangle rect = { (int)m_RectX * 64,0,64,64 };
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, 0, 0, &rect, &color);

	/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawCircle(m_Pos.x, m_Pos.y, m_Radius.x, &color, true);*/
}

void c_Star::Init(Math::Vector2 Pos, Math::Vector2 Target,int LR)
{
	m_Tex.Load("Texture/Star.png");

	m_Pos = Pos;
	m_TGPos = Target;
	float angleDeg;
	if (LR == 1)
	{
		angleDeg = (-90.0f - (rand() % 91)); // -90 ～ -180 の間
	}
	else 
	{
		angleDeg = (0.0f - (rand() % 91));
	}
	float angleRad = DirectX::XMConvertToRadians(angleDeg);

	float speed = 8.0f;

	m_Speed.x = cosf(angleRad) * speed;
	m_Speed.y = sinf(angleRad) * speed;


	m_Scale = 2.0f;
	m_Radius = { 16.0f * m_Scale,16.0f * m_Scale };
	m_RectX = 0;

	m_Conut = 0;

	m_Flg = true;
}

void c_Star::Release()
{
	m_Tex.Release();
}
