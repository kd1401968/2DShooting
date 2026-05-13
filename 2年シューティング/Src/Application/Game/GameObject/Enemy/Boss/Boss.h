#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
enum e_Action {
	StartAction,
	ActionA,
	ActionB,
	ActionC,
	Actic,
	Death,
	EndAction
};
class c_Star;
class c_Mukade;
class c_Gate;
class c_BigGhost;
class c_Thorns;
class c_Spider;
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
	bool GetLast() { return m_LastFlg; }
	float GetAlpha() { return m_Alpha; }
	void SetBossLife();
	e_Action GetAction() { return m_Action; }

	std::vector<c_Star*> mp_Star;
	std::vector<c_Mukade*> mp_Mukade;
	std::vector<c_BigGhost*> mp_BigGhost;
	std::vector<c_Spider*> mp_Spider;
	std::vector<c_Thorns*> mp_Thorns;

private:

	void Init()override;
	void Release()override;

	KdTexture m_Tex;
	KdTexture m_GateTex;

	Math::Matrix m_Mat;
	Math::Matrix m_GateMat[2];

	Math::Vector2 m_Pos;
	Math::Vector2 m_Scale;
	Math::Vector2 m_Radius;
	Math::Vector2 m_Rect;
	Math::Vector2 m_GatePos[2];
	Math::Vector2 m_GateScale;

	e_Action m_Action;

	int m_Life;
	int m_LR;

	bool m_UD;
	bool m_Alive;
	bool m_ShotFlg;
	bool m_DeathFlg;
	bool m_LastFlg;

	float m_GRectX;
	float m_Alpha;
};
