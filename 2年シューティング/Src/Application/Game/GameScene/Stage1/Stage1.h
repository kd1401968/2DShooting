#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameObject/Hit/Hit.h"

class c_Player;
class c_GameUI;
class c_Ghost;
class c_BigGhost;
class Hit;
class c_Explosion;
class c_Eye;
class c_Stage1 :public c_GameSceneBase
{
public:

	c_Stage1(int PlayerLife,int Score) { Init(PlayerLife,Score); }
	~c_Stage1() = default;

	void Init(int PlayerLife,int Score);
	void Release() override;
	void Update() override;
	void Draw() override;

	void HitDec();


	GameSceneType GetSceneType() const override {
		return GameSceneType::Stage1;
	}


	c_Player* m_Player;
	c_GameUI* m_GameUI;
	std::vector<c_Ghost*> mp_Ghost;
	std::vector<c_BigGhost*> mp_BigGhost;
	std::vector<c_Explosion*> mp_Explosion;
	std::vector<c_Eye*> mp_Eye;

private:

	Hit m_Hit;

	KdTexture m_BackTex;
	Math::Matrix m_BackMat;

	Math::Vector2 m_BackPos;
	Math::Vector2 m_StartPos;
	float m_BackMoveX;
	int m_Cnt;
	int m_Intarval;
	int m_PlayerLife;
	int m_Score;

	bool m_StartFlg;
};