#pragma once
enum GameSceneType
{
	Start,
	Stage1,
	Stage2,
	Clear,
	GameOver,
};

class c_GameSceneBase
{
public:

	virtual ~c_GameSceneBase() {}	//デストラクタ
	virtual void Init() {}		//初期化処理
	virtual void Release() {}	//解放処理
	virtual void Update() {}	//更新処理
	virtual void Draw() {}		//描画処理

	virtual GameSceneType GetSceneType() const = 0;

};