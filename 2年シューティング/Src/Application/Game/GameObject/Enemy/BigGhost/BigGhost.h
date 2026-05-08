#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_BigGhost :public c_GameObjectBase
{
public:
	c_BigGhost(Math::Vector2 Pos) { Init(Pos); }
	~c_BigGhost() override { Release(); }

	void Update()override;
	void Draw()override;

	void SetFlg(bool& Flg) { m_Flg = Flg; }
	bool GetFlg() { return m_Flg; }
	Math::Vector2 GetPos() { return m_Pos; }
	void GoGhost();
	void BackGhost();
	void EndFlg();
	Math::Vector2 GetRadius() { return m_Radius; }

private:

	void Init(Math::Vector2 Pos);
	void Release()override;
	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_StartPos;
	Math::Vector2 m_Pos;
	float m_Speed;
	int m_LR;
	float m_RectX;
	float m_Scale;
	bool m_Flg;
	bool m_Move;
	Math::Vector2 m_Radius;
};