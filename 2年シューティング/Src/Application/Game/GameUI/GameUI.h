#pragma once
class c_GameUI
{
public:

	c_GameUI(int Life) { Init(Life); }
	~c_GameUI() { Release(); }

	
	void Update(int i);
	void Draw();

private:

	void Init(int Life);
	void Release();

	static const int LIFE_MAX = 3;
	KdTexture m_LifeTex;
	Math::Matrix m_LifeMat[LIFE_MAX];
	bool m_LifeFlg[LIFE_MAX];
	Math::Vector2 m_LifePos[LIFE_MAX];
	float m_LifeScale;
};