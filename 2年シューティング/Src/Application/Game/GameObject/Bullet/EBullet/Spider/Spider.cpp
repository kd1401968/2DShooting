#include "Spider.h"

void c_Spider::Update()
{
	Math::Matrix S, R, T;

	m_GRectX += 0.5f;
	if (m_GRectX >= 8)
	{
		m_GRectX = 0;
	}
	S = Math::Matrix::CreateScale(m_GateScale.x, m_GateScale.x, 1);
	R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(90));
	T = Math::Matrix::CreateTranslation(0,300, 0);
	m_GateMat[0] = S * R * T;
}

void c_Spider::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	rect = { ((int)m_GRectX * 64), 0, 64, 64 };
	SHADER.m_spriteShader.SetMatrix(m_GateMat[0]);
	SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);

	/*rect = { ((int)m_GRectX * 64) + 32, 0, 32, 64 };
	SHADER.m_spriteShader.SetMatrix(m_GateMat[1]);
	SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);

	rect = { (int)m_GRectX * 64, 0, 32, 64 };
	SHADER.m_spriteShader.SetMatrix(m_GateMat[2]);
	SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);*/

}
void c_Spider::Init()
{
	m_GateTex.Load("Texture/Gate.png");
	m_SpiderTex.Load("Texture/Spider.png");

	m_GateScale={ 1.0f,1.0f };

	m_Count = 0;

	m_Flg = true;
}
void c_Spider::Release()
{
	m_GateTex.Release();
	m_SpiderTex.Release();
}