#include "Title.h"
#include "Application/Scene.h"
#include "Application/Game/Game.h"
void c_Title::Init()
{
	m_BackTex.Load("Texture/NightForest/image.png");
	m_TitleTex.Load("Texture/Title.png");
	m_PressTex.Load("Texture/Start.png");

	m_Alpha = 0.0f;
	m_TitleScale = 1.3f;
	m_PressScale = 0.7f;

	m_TitlePos = { 0.0f,100.0f };
	m_PressPos = { 0.0f,-200.0f };

	m_BackRectX = 0.0f;
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

	m_BackRectX += 1.6f;
	if(m_BackRectX >= 620.0f) {
		m_BackRectX = 0.0f;
	}	

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(0, 0, 0);
	m_BackMat = S * T;

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

	rect = { (int)m_BackRectX,0,620,360};
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);

	rect = { 0,0,460,91 };
	color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_TitleMat);
	SHADER.m_spriteShader.DrawTex(&m_TitleTex, 0, 0, &rect, &color);

	rect = { 0,0,416,92 };
	color = { 1.0f,1.0f,1.0f,m_Alpha };
	SHADER.m_spriteShader.SetMatrix(m_PressMat);
	SHADER.m_spriteShader.DrawTex(&m_PressTex, 0, 0, &rect, &color);
}
