#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_IceBullet :public c_GameObjectBase
{
public:

	c_IceBullet(Math::Vector2 pos,Math::Vector2 targetpos, float scale) { Init(pos,targetpos,scale); }
	~c_IceBullet() override { Release(); }

	void Update()override;
	void Draw()override;

	bool GetFlg() { return m_Flg; }
	Math::Vector2 GetPos() { return m_Pos; }
	Math::Vector2 GetRadius() { return m_Radius; }
	void SetFlg(bool Flg) { m_Flg = Flg; }

private:

	void Init(Math::Vector2 pos, Math::Vector2 targetpos, float scale);
	void Release()override;
	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_Pos;
	Math::Vector2 m_Speed;
	Math::Vector2 m_Radius;
	float m_Scale;
	float m_RectX;
	float m_Rotate;
	bool m_Flg;
};