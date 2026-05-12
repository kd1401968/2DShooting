#pragma once
#include "Application/SceneBase/SceneBase.h"
class c_Result :public c_SceneBase
{
public:

	c_Result(int Score,bool Flg) { Init(Score,Flg); }
	~c_Result()override {Release();};

	void Init(int Score,bool Flg);		//‰Šú‰»ˆ—
	void Release() override;	//‰ğ•úˆ—
	void Update() override;		//XVˆ—
	void Draw() override;		//•`‰æˆ—

private:

	KdTexture m_BackTex;
	KdTexture m_PressTex;
	KdTexture m_EvaTex;
	KdTexture m_ResultTex;

	Math::Matrix m_BackMat;
	Math::Matrix m_PressMat;
	Math::Matrix m_EvaMat;
	Math::Matrix m_ResultMat;

	Math::Vector2 m_PressPos;
	Math::Vector2 m_ResultRect;

	float m_Alpha;

	float m_PressScale;
	float m_PressAlpha;

	int m_Cnt;

	//•\¦‚·‚éŒ…”
	static const int MaxDigits = 8;

	KdTexture m_NumTex;
	unsigned long m_Score = 0;
	Math::Vector2 m_NumPos[MaxDigits];
	Math::Matrix m_NumMat[MaxDigits];
	int m_Digits[MaxDigits] = {};	//ŠeŒ…‚Ì”’l‚ğŠi”[
	float m_NumAlpha;
};