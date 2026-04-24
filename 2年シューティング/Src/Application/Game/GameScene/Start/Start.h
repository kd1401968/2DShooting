#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
class c_Player;
class c_GameUI;
class c_Start :public c_GameSceneBase
{
public:

	c_Start() = default;
	~c_Start() = default;

	void Init() override;
	void Release() override;
	void Update() override;
	void Draw() override;

	GameSceneType GetSceneType() const override {
		return GameSceneType::Start;
	}


	c_Player* m_Player;
	c_GameUI* m_GameUI;

private:

	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	Math::Vector2 m_BackPos;
	float m_BackMoveX;
};