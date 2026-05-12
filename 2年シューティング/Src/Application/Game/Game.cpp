#include "Game.h"
#include "GameScene/Start/Start.h"
#include "GameScene/Stage1/Stage1.h"
#include "GameScene/Stage2/Stage2.h"
void c_Game::Init()
{
	m_PlayerLife = 3;
	m_Score = 0;
	mp_NowGameScene = new c_Start(m_PlayerLife,m_Score);
}

void c_Game::Release()
{
	mp_NowGameScene->Release();
}

void c_Game::Update()
{
	//シーンの更新処理
	if (!m_isTransition)mp_NowGameScene->Update();

	//画面切り替えの更新処理
	if (m_isTransition)TransitionUpdate();

	if (GetAsyncKeyState('4') & 0x8000)
	{
		ChangeGameScene(new c_Start(m_PlayerLife, m_Score));
	}
	if (GetAsyncKeyState('5') & 0x8000)
	{
		ChangeGameScene(new c_Stage1(m_PlayerLife, m_Score));
	}
	if (GetAsyncKeyState('6') & 0x8000)
	{
		ChangeGameScene(new c_Stage2(m_PlayerLife, m_Score));
	}
}

void c_Game::Draw()
{
	//シーンの更新処理
	mp_NowGameScene->Draw();

	//画面切り替えの更新処理
	if (m_isTransition)TransitionDraw();
}

//===================================================================
// 画面切り替え処理
//===================================================================
//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え呼び出し処理
//+++++++++++++++++++++++++++++++++++++++++
void c_Game::ChangeGameScene(c_GameSceneBase* next)
{
	if (m_isTransition)return;	//エラー防止

	//次のシーンを格納
	mp_NextGameScene = next;

	//画面切り替えの初期化処理
	m_isTransition = true;
	TransitionInit();
}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え初期化処理
//+++++++++++++++++++++++++++++++++++++++++
void c_Game::TransitionInit()
{
	//フラグの初期化処理
	m_TransitionFlg = 0;

	m_ScreenAlpha = 0.0f;
	m_ScrennAdd = 0.03f;

}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え更新処理
//+++++++++++++++++++++++++++++++++++++++++
void c_Game::TransitionUpdate()
{
	//フラグ判定から分岐処理
	switch (m_TransitionFlg)
	{
	case 0:
		//フラグ進行処理
		m_TransitionFlg = 1;
		break;

	case 1:

		m_ScreenAlpha += m_ScrennAdd;
		if (m_ScreenAlpha >= 1.0f) {
			m_ScreenAlpha = 1.0f;
			//フラグ進行処理
			m_TransitionFlg = 2;
		}
		break;

	case 2:
		//ポインタの中身を綺麗にする
		if (mp_NowGameScene)
		{
			mp_NowGameScene->Release();
			delete mp_NowGameScene;
		}

		//指定シーンを現在のシーンに格納
		mp_NowGameScene = mp_NextGameScene;

		//指定シーンのポインタの中身を綺麗にする
		mp_NextGameScene = nullptr;

		//シーンの初期化処理
		if (mp_NowGameScene)mp_NowGameScene->Init();


		m_ScrennAdd *= -1;

		//フラグの進行処理
		m_TransitionFlg = 3;
		break;

	case 3:

		mp_NowGameScene->Update();

		m_ScreenAlpha += m_ScrennAdd;
		if (m_ScreenAlpha <= 0.0f) {
			//フラグ進行処理
			m_TransitionFlg = 4;
		}
		break;

	case 4:
		//現在のシーンの更新処理
		mp_NowGameScene->Update();

		//画面切り替え中かどうかを false に戻す
		m_isTransition = false;
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え描画処理
//+++++++++++++++++++++++++++++++++++++++++
void c_Game::TransitionDraw()
{
	//セットアップ
	Math::Color color = { 0.0f,0.0f,0.0f,m_ScreenAlpha };
	D3D.SetBlendState(BlendMode::Alpha);

	//半透明スクリーンの描画
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, 0, 1280, 720, &color, true);

	//セットアップ
	color = { 1.0f,1.0f,1.0f,1.0f };
	D3D.SetBlendState(BlendMode::Alpha);

}