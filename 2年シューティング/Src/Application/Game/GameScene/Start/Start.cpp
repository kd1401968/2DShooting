#include "Start.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameScene/Stage1/Stage1.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
void c_Start::Init(int PlayerLife)
{
	m_StartPos = { 0.0f,0.0f };

	m_BackTex.Load("Texture/NightForest/Image without mist.png");
	m_Player = new c_Player(PlayerLife,m_StartPos);

	m_GameUI = new c_GameUI(PlayerLife);

	m_BackPos = { 0.0f,0.0f };
	m_BackMoveX = 3;

	m_PlayerLife = PlayerLife;
}

void c_Start::Release()
{
	m_BackTex.Release();

	delete m_Player;
	delete m_GameUI;
}

void c_Start::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	m_PlayerLife = 2;
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
		if (game) {
			game->ChangeGameScene(new c_Stage1(m_PlayerLife));
		}

	}


	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0);
	m_BackMat = S * T;
}

void c_Start::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	static float RectX=0;
	//RectX += m_BackMoveX;
	if (RectX <= -620) {
		RectX = 0;
	}
	Rect = { (int)RectX,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);

	m_GameUI->Draw();

	m_Player->Draw();
}
