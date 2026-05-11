#pragma once
#include "Application/SceneBase/SceneBase.h"
class c_Title:public c_SceneBase
{
public:

	c_Title() = default;
	~c_Title() = default;

	void Init() override;		//‰Šú‰»ˆ—
	void Release() override;	//‰ğ•úˆ—
	void Update() override;		//XVˆ—
	void Draw() override;		//•`‰æˆ—

private:

	KdTexture m_BackTex;
	KdTexture m_TitleTex;
	KdTexture m_PressTex;

	Math::Matrix m_BackMat[2];
	Math::Matrix m_TitleMat;
	Math::Matrix m_PressMat;

	Math::Vector2 m_BackPos[2];
	Math::Vector2 m_TitlePos;
	Math::Vector2 m_PressPos;

	float m_TitleScale;
	float m_PressScale;

	float m_Alpha;

};