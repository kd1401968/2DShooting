#pragma once
#include "Application/SceneBase/SceneBase.h"
enum SceneType
{
	Title,//0:タイトル
	Game,//1:ゲーム
	Result//2:リザルト
};
class Scene
{
private:

	c_SceneBase* mp_NowScene = nullptr;
	c_SceneBase* mp_NextScene = nullptr;

public:

	// 初期設定
	void Init();

	// 解放
	void Release();

	// 更新処理
	void Update();

	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	void ChangeScene(c_SceneBase* next);

private:

	Scene() {}

public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()
