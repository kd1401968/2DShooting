#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_Spider : public c_GameObjectBase
{
public:
	c_Spider() { Init(); }
	~c_Spider()override { Release(); }

	void Update()override;
	void Draw()override;

	bool GetFlg() { return m_Flg; }

private:

	void Init();
	void Release();

	KdTexture m_SpiderTex;
	KdTexture m_GateTex;

	int m_Count;

	float m_GRectX;

	Math::Matrix m_GateMat[3];

	Math::Vector2 m_GateScale;

	bool m_Flg;

};