#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameObject/Hit/Hit.h"

class c_Player;
class c_GameUI;
class c_Ghost;
class Hit;
class c_Explosion;
class c_Stage1 :public c_GameSceneBase
{
public:

	c_Stage1() = default;
	~c_Stage1() = default;

	void Init() override;
	void Release() override;
	void Update() override;
	void Draw() override;

	GameSceneType GetSceneType() const override {
		return GameSceneType::Stage1;
	}


	c_Player* m_Player;
	c_GameUI* m_GameUI;
	std::vector<c_Ghost*> mp_Ghost;
	std::vector<c_Explosion*> mp_Explosion;

private:

	Hit m_Hit;

	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	Math::Vector2 m_BackPos;
	float m_BackMoveX;
};