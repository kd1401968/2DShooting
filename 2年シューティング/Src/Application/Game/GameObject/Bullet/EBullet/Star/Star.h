#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_Star : public c_GameObjectBase{
public:

	c_Star(Math::Vector2 Pos,Math::Vector2 Target) { Init(Pos,Target); }
	~c_Star() override{ Release(); }

	void Update()override;
	void Draw()override;

	bool GetFlg() { return m_Flg; }
	Math::Vector2 GetPos() { return m_Pos; }
	Math::Vector2 GetRadius() { return m_Radius; }

	void SetFlg(bool Flg) { m_Flg = Flg; }

private:

	void Init(Math::Vector2 Pos, Math::Vector2 Target);
	void Release()override;

	KdTexture m_Tex;

	Math::Matrix m_Mat;

	Math::Vector2 m_TGPos;
	Math::Vector2 m_Pos;
	Math::Vector2 m_Speed;
	Math::Vector2 m_Radius;

	float m_Scale;
	float m_RectX;

	int m_Conut;

	bool m_Flg;
};