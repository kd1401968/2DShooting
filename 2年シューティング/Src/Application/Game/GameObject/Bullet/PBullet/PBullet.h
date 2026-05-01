#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_PBullet :public c_GameObjectBase
{
public:
	c_PBullet(Math::Vector2 Pos,int LR) { Init(Pos,LR); }
	~c_PBullet() override{ Release(); }

	
	void Update()override;
	void Draw()override;

	Math::Vector2 GetPos(){ return m_Pos; }
	Math::Vector2 GetRadius() { return { 32.0f,32.0f }; }
	bool GetFlg() { return m_Flg; }
	void SetFlg(bool Flg) { m_Flg = Flg; }
	

private:

	void Init(Math::Vector2 Pos,int LR);
	void Release()override;

	KdTexture m_Tex;
	Math::Matrix m_Mat;
	Math::Vector2 m_Pos;
	Math::Vector2 m_Speed;
	bool m_Flg;
	float m_RectX;
	int m_LR;
};