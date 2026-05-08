#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_Ghost :public c_GameObjectBase
{
public:
	c_Ghost(Math::Vector2 Pos) { Init(Pos); }
	~c_Ghost() override{ Release(); }


	void Update()override;
	void Draw()override;

	Math::Vector2 GetPos() { return m_Pos; }
	Math::Vector2 GetRadius() { return { 30.0f,25.0f }; }
	bool GetFlg() { return m_Flg; }
	//void AbsSetFlg(bool Flg);
	void SetFlg(bool& Flg) {m_Flg = Flg;};


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
	float m_Alpha;
	Math::Vector2 m_Radius;
	Math::Vector2 m_Scale;
};