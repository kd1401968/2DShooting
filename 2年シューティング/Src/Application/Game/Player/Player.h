#pragma once
class c_GameSceneBase;
class c_Player
{
public:

	c_GameSceneBase *m_NowScene;

	c_Player() {}
	~c_Player() {}

	void Init();
	void Update();
	void Draw();
	void Release();



private:
};