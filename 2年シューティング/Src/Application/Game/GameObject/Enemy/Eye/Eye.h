#pragma once
#include "Application/Game/GameObject/GameObjectBase.h"
class c_IceBullet;
class c_Eye : public c_GameObjectBase {
public:

	c_Eye(float x, float y, float scale) {Init(x, y, scale); };
	~c_Eye() override{ Release(); };

	void Update(float tX,float tY);
	void Draw() override;

	bool GetFlg() { return m_Flg; }

	c_IceBullet* m_IceBullet = nullptr;

private:

	void Init(float x,float y,float scale);
	void Release()override;
	Math::Vector2 m_Pos[3];//ÇªÇÍÇºÇÍÇÃä·ÇÃç¿ïW
	float m_Scale;
	float m_Rotate;
	float m_RotateDelta;
	float m_Alpha;
	int m_Count;
	bool m_Invisible;
	bool m_Flg;
	bool m_MoveFlg;

	KdTexture Eye1Tex;	//ñ⁄
	KdTexture Eye2Tex;	//çïñ⁄ÇÃå„ÇÎ
	KdTexture Eye3Tex;	//çïñ⁄

	Math::Matrix Eye1Mat;
	Math::Matrix Eye2Mat;
	Math::Matrix Eye3Mat;
};