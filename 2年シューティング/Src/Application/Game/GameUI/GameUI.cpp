#include "Application/Game/GameUI/GameUI.h"
void c_GameUI::Init(int Life,int Score) 
{
	m_LifeTex.Load("Texture/Life.png");
	for (int i = 0; i < LIFE_MAX; i++)
	{
		m_LifeMat[i] = Math::Matrix::Identity;
		if (i > Life)
		{
			m_LifeFlg[i] = false;
		}
		else
		{
			m_LifeFlg[i] = true;
		}
		m_LifePos[i] = { -580.0f + i * 80.0f, -320.0f };
	}
	m_LifeScale = 0.25f;

	m_NumTex.Load("Texture/number.png");

	m_Score = Score;

	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; i--)
	{
		//下位の桁から抽出し配列に格納
		m_Digits[i] = tmp % 10;//余りを求める演算子　% 
		tmp /= 10;//商を求める演算子　/

		float posX = -300;
		m_NumPos[i].x = posX + (i * 70);
		m_NumPos[i].y = 0;
	}
}
void c_GameUI::Update(int i)
{
	// 現在のライフ数を数える
	int life = 0;
	for (int j = 0; j < LIFE_MAX; j++) {
		if (m_LifeFlg[j]) life++;
	}

	// 減っていたら false にする
	for (int j = i; j < LIFE_MAX; j++) {
		m_LifeFlg[j] = false;
	}

	Math::Matrix S, R, T;


	//配列に各桁の数値を格納
	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; i--)
	{
		//下位の桁から抽出し配列に格納
		m_Digits[i] = tmp % 10;//余りを求める演算子　% 
		tmp /= 10;//商を求める演算子　/

		float posX = 200;
		m_NumPos[i].x=posX + (i * 56);
		m_NumPos[i].y = -320;

		S = Math::Matrix::CreateScale(8, 8, 1);
		T = Math::Matrix::CreateTranslation(m_NumPos[i].x, m_NumPos[i].y, 0);
		m_NumMat[i] = S * T;
	}


	for (int j = 0; j < LIFE_MAX; j++) {
		Math::Matrix S, R, T;
		S = Math::Matrix::CreateScale(m_LifeScale);
		T = Math::Matrix::CreateTranslation(m_LifePos[j].x, m_LifePos[j].y, 0.0f);
		m_LifeMat[j] = S * T;
	}
}
void c_GameUI::Draw()
{
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -320, 640, 40, &color, true);


	Math::Rectangle rect = { 0,0,457,393 };
	for (int i = 0; i < LIFE_MAX; i++) {
		if (m_LifeFlg[i]) {
			color = { 1.0f,1.0f,1.0f,1.0f };
		}
		else {
			color = { 0.1f,0.1f,0.1f,0.5f };
		}
		SHADER.m_spriteShader.SetMatrix(m_LifeMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_LifeTex, rect, color);
	}

	//スコア表示
	for (int i = 0; i < MaxDigits; i++)
	{
		Math::Rectangle rc = { 7 * m_Digits[i],0,7,10 };
		color = { 1.0f,1.0f,1.0f,1.0f };

		

		//表示（サイズ１０倍）
		SHADER.m_spriteShader.SetMatrix(m_NumMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_NumTex,0, 0, &rc,&color);

		/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(m_NumPos[i].x, m_NumPos[i].y, 10, 10, &color, true);*/

	}
	
}
void c_GameUI::Release()
{
	m_LifeTex.Release();
	m_NumTex.Release();
}