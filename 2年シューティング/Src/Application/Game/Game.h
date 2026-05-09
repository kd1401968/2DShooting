#pragma once
#include "Application/SceneBase/SceneBase.h"
#include "Application/Game/GameScene/GameSceneBase.h"
//enum GameSceneType
//{
//	Start,
//	Stage1,
//	Stage2,
//	Clear,
//	GameOver,
//};
class c_Game :public c_SceneBase
{
public:


	c_GameSceneBase* mp_NowGameScene = nullptr;
	c_GameSceneBase* mp_NextGameScene = nullptr;


	c_Game() = default;
	~c_Game() = default;

	void Init() override;
	void Release() override;
	void Update() override;
	void Draw() override;

	void ChangeGameScene(c_GameSceneBase* next);

	GameSceneType GetNowSceneType() const {
		if (mp_NowGameScene == nullptr) return GameSceneType::Start; // 初期値など
		return mp_NowGameScene->GetSceneType();
	}



private:

	//---------------------
	// 画面切り替え処理
	//---------------------
	void TransitionInit();		//画面切り替え初期化処理
	void TransitionUpdate();	//画面切り替え更新処理
	void TransitionDraw();		//画面切り替え描画処理

	bool m_isTransition;				//画面切り替え中かどうか
	int m_TransitionFlg;				//画面切り替えのフラグ

	float m_ScreenAlpha;
	float m_ScrennAdd;

	int m_PlayerLife;
};