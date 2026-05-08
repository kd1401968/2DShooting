#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_IceBullet :public c_GameObjectBase
{
public:

	c_IceBullet(Math::Vector2 pos,float scale) { Init(pos,scale); }
	~c_IceBullet() override { Release(); }

	void Update()override;
	void Draw()override;

	bool GetFlg() { return m_Flg; }

private:

	void Init(Math::Vector2 pos,float scale);
	void Release()override;
	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_Pos;
	Math::Vector2 m_Speed;
	float m_Scale;
	bool m_Flg;
};