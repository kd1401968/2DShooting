#pragma once
class c_GameUI
{
public:

	c_GameUI(int Life,int Score) { Init(Life,Score); }
	~c_GameUI() { Release(); }

	
	void Update(int i);
	void Draw();

	int GetScore() { return m_Score; }
	void SetScore(int Addscore) { m_Score += Addscore; }

private:

	void Init(int Life,int Score);
	void Release();

	static const int LIFE_MAX = 3;
	KdTexture m_LifeTex;
	Math::Matrix m_LifeMat[LIFE_MAX];
	bool m_LifeFlg[LIFE_MAX];
	Math::Vector2 m_LifePos[LIFE_MAX];
	float m_LifeScale;

	//•\¦‚·‚éŒ…”
	static const int MaxDigits = 8;

	KdTexture m_NumTex;
	unsigned long m_Score = 0;
	Math::Vector2 m_NumPos[MaxDigits];
	Math::Matrix m_NumMat[MaxDigits];
	int m_Digits[MaxDigits] = {};	//ŠeŒ…‚Ì”’l‚ğŠi”[
};