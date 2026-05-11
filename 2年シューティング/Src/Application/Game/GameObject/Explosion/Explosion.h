#pragma once
class c_Explosion
{
public:

	c_Explosion() {}
	~c_Explosion() { Release(); }
	void Init(Math::Vector2 Pos,float Scale);
	void Update();
	void Draw();

	bool GetFlg() { return m_Flg; }

private:
	void Release();

	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_Pos;
	float m_Scale;
	bool m_Flg;
	float m_Anime;
};