#include "Thorns.h"

void c_Thorns::Update()
{
	m_Count++;
	if (m_Count <= 40)
	{
		m_AddGateScale.x += 0.2f;
		if (m_AddGateScale.x >= 5.0f)
		{
			m_AddGateScale.x = 5.0f;
		}
		m_AddGateScale.y += 4.0f;
		if (m_AddGateScale.y >= 22.0f)
		{
			m_AddGateScale.y = 22.0f;
		}
	}
	else
	{
		m_AddBoxPos.y+=2;
		if (m_AddBoxPos.y >= 145&&!m_EndFlg)
		{
			m_AddBoxPos.y = 145;
			m_ThornsPos.y = -165;
			if (m_Count >= 130)
			{
				m_EndFlg = true;
			}
		}
	}

	if (m_EndFlg)
	{
		m_ThornsPos.y-=6;
		if (m_ThornsPos.y <= -480)
		{
			m_ThornsPos.y = -480;
			m_AddGateScale.x -= 0.2f;
			if (m_AddGateScale.x <= 0.0f)
			{
				m_AddGateScale.x = 0.0f;
			}
			m_AddGateScale.y -= 4.0f;
			if (m_AddGateScale.y <= 0.0f)
			{
				m_AddGateScale.y = 0.0f;
				m_Flg = false;
			}
		}
	}

	Math::Matrix S, R, T;

	m_GRectX += 0.5f;
	if (m_GRectX >= 8)
	{
		m_GRectX = 0;
	}
	//m_GateScale = { 5,22 };
	S = Math::Matrix::CreateScale(m_AddGateScale.x*-1, m_AddGateScale.y, 1);
	R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
	T = Math::Matrix::CreateTranslation(m_GatePos[0].x, m_GatePos[0].y, 0);
	m_GateMat[0] = S * R * T;

	for (int i = 1; i < 3; i++)
	{
		S = Math::Matrix::CreateScale(m_AddGateScale.x*-1, m_AddGateScale.y, 1);
		R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
		T = Math::Matrix::CreateTranslation(m_GatePos[i].x + m_GatePos[0].x, m_GatePos[i].y + m_GatePos[0].y + 80, 0);
		m_GateMat[i] = S * R * T;
	}

	S = Math::Matrix::CreateScale(0.6, 0.5, 1);
	T = Math::Matrix::CreateTranslation(m_ThornsPos.x ,m_ThornsPos.y, 0);
	m_ThornsMat = S * T;
}

void c_Thorns::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	if (m_Count <= 30)
	{
		rect = { ((int)m_GRectX * 64), 0, 64, 64 };
		SHADER.m_spriteShader.SetMatrix(m_GateMat[0]);
		SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);
	}
	else
	{
		rect = { (int)m_GRectX * 64, 0, 32, 64 };
		SHADER.m_spriteShader.SetMatrix(m_GateMat[2]);
		SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);

		if (m_AddBoxPos.y != 145&&!m_EndFlg)
		{
			color = { 1.0f,0.0f,0.0f,0.3f };
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
			SHADER.m_spriteShader.DrawBox(m_BoxPos.x, m_BoxPos.y, 394, 145, &color, true);
			color = { 1.0f,0.0f,0.0f,0.2f };
			SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
			SHADER.m_spriteShader.DrawBox(m_AddBoxPos.x, m_AddBoxPos.y - 290, 394, m_AddBoxPos.y, &color, true);
		}

		rect = {0,0,1350,784};
		color = { 0.3f,0.3f,0.3f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_ThornsMat);
		SHADER.m_spriteShader.DrawTex(&m_ThornsTex, 0, 0, &rect, &color);

		color = { 1.0f,1.0f,1.0f,1.0f };
		rect = { ((int)m_GRectX * 64) + 32, 0, 32, 64 };
		SHADER.m_spriteShader.SetMatrix(m_GateMat[1]);
		SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);
	}


}
void c_Thorns::Init()
{
	m_GateTex.Load("Texture/Gate.png");
	m_ThornsTex.Load("Texture/Thorns.png");

	m_GateScale = { 5.0f,22.0f };
	m_AddGateScale = { 0,0 };
	m_GatePos[0] = { 20,-270 };
	m_GatePos[1] = { 0,-160 };
	m_GatePos[2] = { 0,0 };
	m_AddBoxPos = { 40,0 };
	m_BoxPos = { 40,-145 };
	m_ThornsPos = { 50,-400 };

	m_Count = 0;

	m_EndFlg = false;
	m_Flg = true;
	m_AttackFlg = true;
}
void c_Thorns::Release()
{
	m_GateTex.Release();
	m_ThornsTex.Release();
}