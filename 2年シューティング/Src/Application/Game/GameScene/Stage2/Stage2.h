#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameObject/Hit/Hit.h"

class c_Player;
class c_GameUI;
class Hit;
class c_Explosion;
class c_Stage2 :public c_GameSceneBase
{
public:

	c_Stage2(int PlayerLife) { Init(PlayerLife); }
	~c_Stage2() = default;

	
	void Update() override;
	void Draw() override;

	void HitDec();


	GameSceneType GetSceneType() const override {
		return GameSceneType::Stage1;
	}


	c_Player* m_Player;
	c_GameUI* m_GameUI;
	std::vector<c_Explosion*> mp_Explosion;

private:

	void Init(int PlayerLife);
	void Release() override;

	Hit m_Hit;

	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	Math::Vector2 m_BackPos;
	Math::Vector2 m_StartPos;

	bool m_StartFlg;
};