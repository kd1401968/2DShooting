#include "Title.h"
#include "Application/Scene.h"
#include "Application/Game/Game.h"
void c_Title::Init()
{
	m_BackTex.Load("Texture/NightForest/Image(1).png");
	m_TitleTex.Load("Texture/Title.png");
	m_PressTex.Load("Texture/Start.png");

	m_Alpha = 0.0f;
	m_TitleScale = 1.3f;
	m_PressScale = 0.7f;

	m_TitlePos = { 0.0f,100.0f };
	m_PressPos = { 0.0f,-200.0f };


	m_BackPos[0] = { 0,0 };
	m_BackPos[1] = { 1280,0 };
}

void c_Title::Release()
{
	m_BackTex.Release();
	m_TitleTex.Release();
	m_PressTex.Release();
}

void c_Title::Update()
{

	if (GetAsyncKeyState(VK_RETURN)&(0x8000)) {
		SCENE.ChangeScene(new c_Game());
	}

	static bool invisible = false;
	if(invisible) {
		m_Alpha -= 0.01f;
		if (m_Alpha <= 0.0f) {
			m_Alpha = 0.0f;
			invisible = false;
		}
	}
	else {
		m_Alpha += 0.01f;
		if (m_Alpha >= 1.0f) {
			m_Alpha = 1.0f;
			invisible = true;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_BackPos[i].x -= 3.2f;
		if (m_BackPos[i].x <= -1280)
		{
			m_BackPos[i].x = 1280;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2.6, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos[0].x, m_BackPos[0].y, 0);
	m_BackMat[0] = S * T;

	S = Math::Matrix::CreateScale(2.09*-1, 2.6, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos[1].x, m_BackPos[1].y, 0);
	m_BackMat[1] = S * T;

	S = Math::Matrix::CreateScale(m_TitleScale, m_TitleScale, 1);
	T = Math::Matrix::CreateTranslation(m_TitlePos.x, m_TitlePos.y, 0);
	m_TitleMat = S * T;

	S = Math::Matrix::CreateScale(m_PressScale, m_PressScale, 1);
	T = Math::Matrix::CreateTranslation(m_PressPos.x, m_PressPos.y, 0);
	m_PressMat = S * T;
}

void c_Title::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	for (int i = 0; i < 2; i++)
	{
		rect = { 0,0,620,360 };
		SHADER.m_spriteShader.SetMatrix(m_BackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);
	}


	rect = { 0,0,460,91 };
	color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_TitleMat);
	SHADER.m_spriteShader.DrawTex(&m_TitleTex, 0, 0, &rect, &color);

	rect = { 0,0,416,92 };
	color = { 1.0f,1.0f,1.0f,m_Alpha };
	SHADER.m_spriteShader.SetMatrix(m_PressMat);
	SHADER.m_spriteShader.DrawTex(&m_PressTex, 0, 0, &rect, &color);
}
