#pragma once
#include "Application/Game/GameScene/GameSceneBase.h"
class c_Start :public c_GameSceneBase
{
public:

	c_Start() = default;
	~c_Start() = default;

	void Init() override;
	void Release() override;
	void Update() override;
	void Draw() override;

private:
};