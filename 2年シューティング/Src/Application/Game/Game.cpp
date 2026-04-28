#include "Game.h"
#include "GameScene/Start/Start.h"
#include "GameScene/Stage1/Stage1.h"
void c_Game::Init()
{
	mp_NowGameScene = new c_Stage1;
	mp_NowGameScene->Init();
}

void c_Game::Release()
{
	mp_NowGameScene->Release();
}

void c_Game::Update()
{
	mp_NowGameScene->Update();
}

void c_Game::Draw()
{
	mp_NowGameScene->Draw();
}

void c_Game::ChangeScene(c_GameSceneBase* next)
{
	//次のシーンを格納
	mp_NextGameScene = next;


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
}
