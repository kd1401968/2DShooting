#include "main.h"
#include "Scene.h"
#include "Application/Title/Title.h"
void Scene::Draw2D()
{
	mp_NowScene->Draw();
}

void Scene::Update()
{
	mp_NowScene->Update();
}

void Scene::Init()
{
	mp_NowScene = new c_Title();
	mp_NowScene->Init();
}

void Scene::Release()
{
	//シーンの解放処理
	if (mp_NowScene)
	{
		mp_NowScene->Release();	//アドレス先も解放処理を行う
		delete mp_NowScene;		//deleteしてメモリリークを防ぐ
		mp_NowScene = nullptr;	//nullptrで中身を空にする
	}
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
void Scene::ChangeScene(c_SceneBase* next)
{

	//次のシーンを格納
	mp_NextScene = next;


	if (mp_NowScene)
	{
		mp_NowScene->Release();
		delete mp_NowScene;
	}

	//指定シーンを現在のシーンに格納
	mp_NowScene = mp_NextScene;

	//指定シーンのポインタの中身を綺麗にする
	mp_NextScene = nullptr;

	//シーンの初期化処理
	if (mp_NowScene)mp_NowScene->Init();

}

