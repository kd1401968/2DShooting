#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameObject/Hit/Hit.h"

class c_Player;
class c_GameUI;
class Hit;
class c_Explosion;
class c_Rain;
class c_Boss;
class c_Stage2 :public c_GameSceneBase
{
public:

	c_Stage2(int PlayerLife,int Score) { Init(PlayerLife,Score); }
	~c_Stage2() = default;

	
	void Update() override;
	void Draw() override;

	void HitDec2();


	GameSceneType GetSceneType() const override {
		return GameSceneType::Stage2;
	}


	c_Player* m_Player;
	c_GameUI* m_GameUI;
	std::vector<c_Explosion*> mp_Explosion;
	

private:

	void Init(int PlayerLife,int Score);
	void Release() override;

	Hit m_Hit;

	Math::Matrix m_BackMat[2];

	Math::Vector2 m_BackPos[2];

	KdTexture m_BackTex;

	Math::Vector2 m_StartPos;

	bool m_StartFlg;

	c_Boss* m_Boss = nullptr;

	//パーティクル
	//雨用
	std::vector<c_Rain*>m_Rain;

	int m_RainNum;
	//Particle rain[rainNum];
	KdTexture m_RainTex;//ロード用
};