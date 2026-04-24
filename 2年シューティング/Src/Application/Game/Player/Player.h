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

	int SetLife() { return m_Life; }
	int SetLR() { return m_LR; }
	bool SetAlive() { return m_Alive; }

private:

	void Release();

	Math::Vector2 m_Pos;
	KdTexture m_Tex;
	KdTexture m_AttackTex;
	Math::Matrix m_Mat;
	float m_Scale;
	float m_Speed;
	int m_Life;
	int m_LR;
	float m_Rect;
	float m_AttackRect;
	bool m_Alive;
	int m_Interval;
};