#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_Ghost :public c_GameObjectBase
{
public:
	c_Ghost(Math::Vector2 Pos) { Init(Pos); }
	~c_Ghost() override{ Release(); }


	void Update()override;
	void Draw()override;

	bool GetFlg() { return m_Flg; }


private:

	void Init(Math::Vector2 Pos);
	void Release()override;

	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_Pos;
	Math::Vector2 m_Speed;
	bool m_Flg;
	float m_RectX;
	int m_LR;
	Math::Vector2 m_Radius;
	Math::Vector2 m_Scale;
};