#include "Result.h"
#include "Application/Scene.h"
#include "Application/Title/Title.h"
void c_Result::Init(int Score, bool Flg)
{
	m_BackTex.Load("Texture/Back.png");
	m_PressTex.Load("Texture/Start.png");

	if (Flg == true)
	{
		m_EvaTex.Load("Texture/S.png");
	}
	else
	{
		m_EvaTex.Load("Texture/B.png");
	}

	m_Alpha = 0.0f;

	m_Cnt = 0;

	m_NumTex.Load("Texture/number.png");

	m_Score = Score;

	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; i--)
	{
		//下位の桁から抽出し配列に格納
		m_Digits[i] = tmp % 10;//余りを求める演算子　% 
		tmp /= 10;//商を求める演算子　/

		float posX = 300;
		m_NumPos[i].x = posX + (i * 70);
		m_NumPos[i].y = 0;
	}

	m_NumAlpha = 0.0f;

	m_PressScale = 0.7f;

	m_PressPos = { 0.0f,-300.0f };

	m_PressAlpha = 0.0f;
}

void c_Result::Release()
{
	m_BackTex.Release();
	m_EvaTex.Release();
	m_NumTex.Release();
}

void c_Result::Update()
{
	m_Cnt++;

	if (m_Cnt >= 60)
	{
		m_NumAlpha = 1.0f;
	}
	if (m_Cnt >= 90)
	{
		m_Alpha = 1.0f;
	}
	if (m_Cnt >= 150)
	{
		if (GetAsyncKeyState(VK_RETURN) & (0x8000)) {
			SCENE.ChangeScene(new c_Title());
		}

		static bool invisible = false;
		if (invisible) {
			m_PressAlpha -= 0.01f;
			if (m_PressAlpha <= 0.0f) {
				m_PressAlpha = 0.0f;
				invisible = false;
			}
		}
		else {
			m_PressAlpha += 0.01f;
			if (m_PressAlpha >= 1.0f) {
				m_PressAlpha = 1.0f;
				invisible = true;
			}
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(0.8, 0.8, 1);
	T = Math::Matrix::CreateTranslation(-300, 0, 0);
	m_EvaMat = S * T;

	//配列に各桁の数値を格納
	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; i--)
	{
		//下位の桁から抽出し配列に格納
		m_Digits[i] = tmp % 10;//余りを求める演算子　% 
		tmp /= 10;//商を求める演算子　/

		float posX = 70;
		m_NumPos[i].x = posX + (i * 70);
		m_NumPos[i].y = -100;

		S = Math::Matrix::CreateScale(10, 10, 1);
		T = Math::Matrix::CreateTranslation(m_NumPos[i].x, m_NumPos[i].y, 0);
		m_NumMat[i] = S * T;
	}

	S = Math::Matrix::CreateScale(m_PressScale, m_PressScale, 1);
	T = Math::Matrix::CreateTranslation(m_PressPos.x, m_PressPos.y, 0);
	m_PressMat = S * T;
}

void c_Result::Draw()
{
	Math::Rectangle rect;
	Math::Color color;

	rect = { 0,0,1280,720 };
	color = { 0.7f,0.7f,0.7f,1.0f };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);

	rect = { 0,0,1024,1024 };
	color = { 1.0f,1.0f,1.0f,m_Alpha };
	SHADER.m_spriteShader.SetMatrix(m_EvaMat);
	SHADER.m_spriteShader.DrawTex(&m_EvaTex, 0, 0, &rect, &color);

	for (int i = 0; i < MaxDigits; i++)
	{
		Math::Rectangle rc = { 7 * m_Digits[i],0,7,10 };
		color = { 1.0f,1.0f,1.0f,m_NumAlpha };

		//表示（サイズ１０倍）
		SHADER.m_spriteShader.SetMatrix(m_NumMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_NumTex, 0, 0, &rc, &color);

	}

	rect = { 0,0,416,92 };
	color = { 1.0f,1.0f,1.0f,m_PressAlpha };
	SHADER.m_spriteShader.SetMatrix(m_PressMat);
	SHADER.m_spriteShader.DrawTex(&m_PressTex, 0, 0, &rect, &color);
}
