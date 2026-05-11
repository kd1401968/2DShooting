#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameObject/Hit/Hit.h"

class c_Player;
class c_GameUI;
class Hit;
class c_Explosion;

class c_Start :public c_GameSceneBase
{
public:

	c_Start(int PlayerLife,int Score) { Init(PlayerLife,Score); }
	~c_Start() = default;

	void Init(int PlayerLife,int Score);
	void Release() override;
	void Update() override;
	void Draw() override;

	GameSceneType GetSceneType() const override {
		return GameSceneType::Start;
	}

	c_Player* m_Player;
	c_GameUI* m_GameUI;
	std::vector<c_Explosion*> mp_Explosion;

private:

	KdTexture m_BackTex;
	KdTexture m_ChainTex;
	KdTexture m_PlayerTex;
	KdTexture m_BulletTex;
	KdTexture m_SignTex;
	KdTexture m_PresonTex;
	KdTexture m_KeyTex[2];

	Math::Matrix m_BackMat;
	Math::Matrix m_ChainMat[3];
	Math::Matrix m_PlayerMat[3];
	Math::Matrix m_BulletMat;
	Math::Matrix m_SignMat[2];
	Math::Matrix m_PresonMat;
	Math::Matrix m_KeyMat[2];

	int m_ChainRectY[3];
	int m_PlayerRectX[3];

	Math::Vector2 m_KeyRect[2];

	int m_Cnt;


	Math::Vector2 m_BackPos;
	float m_BackMoveX;

	int m_PlayerLife;
	int m_Score;
	Math::Vector2 m_StartPos;

	Hit m_Hit;
};