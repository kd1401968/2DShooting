#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
enum e_Action {
	StartAction,
	ActionA,
	ActionB,
	ActionC,
	Death,
	EndAction
};
class c_Star;
class c_Mukade;
class c_Gate;
class c_Boss :public c_GameObjectBase
{
public:

	c_Boss() { Init(); }
	~c_Boss()override { Release(); }

	void Update(Math::Vector2 Pos);
	void Draw()override;

	Math::Vector2 GetPos() { return m_Pos; }
	Math::Vector2 GetRadius() { return m_Radius; }
	int GetLife() { return m_Life; }
	bool GetDeath() { return m_DeathFlg; }
	void SetBossLife();

	std::vector<c_Star*> mp_Star;
	std::vector<c_Mukade*> mp_Mukade;

private:

	void Init()override;
	void Release()override;

	e_Action m_Action;

	KdTexture m_Tex;
	KdTexture m_GateTex;

	Math::Matrix m_Mat;
	Math::Matrix m_GateMat[3];

	Math::Vector2 m_Pos;
	Math::Vector2 m_Scale;
	Math::Vector2 m_Radius;
	Math::Vector2 m_Rect;
	Math::Vector2 m_GatePos[3];
	Math::Vector2 m_GateScale;

	int m_Life;
	int m_LR;

	bool m_UD;
	bool m_Alive;
	bool m_ShotFlg;
	bool m_DeathFlg;

	float m_GRectX;
};
