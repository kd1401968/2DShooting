#pragma once
class c_GameSceneBase;
class c_PBullet;
class c_Player
{
public:

	c_GameSceneBase *m_NowScene;
	std::vector<c_PBullet*> mp_Bullet;

	c_Player() {}
	~c_Player() { Release(); }

	void Init();
	void Update();
	void Draw();

	int GetLife() { return m_Life; }
	int GetLR() { return m_LR; }
	bool GetAlive() { return m_Alive; }
	void SetBulletFlg(bool flg,int i);
	Math::Vector2 GetPos() { return m_Pos; }
	void SetPos(Math::Vector2 Pos) { m_Pos = Pos; }
	Math::Vector2 GetRadius() { return m_Radius; }
	void SetLife();
	float GetAlpha() { return m_Alpha; }

private:

	void Release();

	Math::Vector2 m_Pos;
	KdTexture m_Tex;
	KdTexture m_AttackTex;
	Math::Matrix m_Mat;
	float m_Scale;
	Math::Vector2 m_Speed;
	int m_Life;
	int m_LR;
	float m_Rect;
	float m_AttackRect;
	bool m_Alive;
	int m_Interval;
	int m_Count;
	float m_Alpha;
	Math::Vector2 m_Radius;
};