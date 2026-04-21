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

	Math::Matrix m_BackMat;
};