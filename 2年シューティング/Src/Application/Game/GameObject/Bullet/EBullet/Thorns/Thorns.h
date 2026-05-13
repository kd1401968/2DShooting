#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_Thorns : public c_GameObjectBase
{
public:
	c_Thorns() { Init(); }
	~c_Thorns()override { Release(); }

	void Update()override;
	void Draw()override;

	Math::Vector2 GetPos() { return m_AddBoxPos; }
	Math::Vector2 GetHitPos() { return m_BoxPos; }
	Math::Vector2 GetRadius() { return { 394,145 }; }
	bool GetFlg() { return m_Flg; }
	bool GetAttackFlg() { return m_AttackFlg; }
	void SetAttackFlg(bool flg) {	m_AttackFlg = flg; }

private:

	void Init();
	void Release();

	KdTexture m_ThornsTex;
	KdTexture m_GateTex;

	int m_Count;

	float m_GRectX;

	Math::Matrix m_GateMat[3];
	Math::Matrix m_ThornsMat;

	Math::Vector2 m_GateScale;
	Math::Vector2 m_GatePos[3];
	Math::Vector2 m_AddGateScale;
	Math::Vector2 m_ThornsPos;
	Math::Vector2 m_BoxPos;
	Math::Vector2 m_AddBoxPos;

	bool m_Flg;
	bool m_EndFlg;
	bool m_AttackFlg;
};