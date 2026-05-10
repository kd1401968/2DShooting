#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
enum e_Action {
	StartAction,
	ActionA,
	ActionB,
	ActionC,
	EndAction
};
class c_Star;
class c_Boss :public c_GameObjectBase
{
public:

	c_Boss() { Init(); }
	~c_Boss()override { Release(); }

	void Update(Math::Vector2 Pos);
	void Draw()override;

	Math::Vector2 GetPos() { return m_Pos; }
	Math::Vector2 GetRadius() { return m_Radius; }
	void SetBossLife();

	std::vector<c_Star*> mp_Star;

private:

	void Init()override;
	void Release()override;

	e_Action m_Action;

	KdTexture m_Tex;

	Math::Matrix m_Mat;

	Math::Vector2 m_Pos;
	Math::Vector2 m_Scale;
	Math::Vector2 m_Radius;
	Math::Vector2 m_Rect;

	int m_Life;
	int m_LR;

	bool m_UD;
	bool m_Alive;
	bool m_ShotFlg;

};
