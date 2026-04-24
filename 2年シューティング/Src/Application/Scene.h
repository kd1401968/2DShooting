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

	float m_ScreenAlpha;
	float m_ScrennAdd;

	bool m_isTransition;				//画面切り替え中かどうか
	int m_TransitionFlg;				//画面切り替えのフラグ


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

	//---------------------
	// 画面切り替え処理
	//---------------------
	void TransitionInit();		//画面切り替え初期化処理
	void TransitionUpdate();	//画面切り替え更新処理
	void TransitionDraw();		//画面切り替え描画処理

	c_SceneBase* GetNowScene() const { return mp_NowScene; }



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
