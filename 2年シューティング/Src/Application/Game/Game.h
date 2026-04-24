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

	void ChangeScene(c_GameSceneBase* next);

	GameSceneType GetNowSceneType() const {
		if (mp_NowGameScene == nullptr) return GameSceneType::Start; // ‰Šú’l‚È‚Ç
		return mp_NowGameScene->GetSceneType();
	}


private:
};