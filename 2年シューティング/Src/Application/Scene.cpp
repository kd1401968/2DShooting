#include "main.h"
#include "Scene.h"
#include "Application/Title/Title.h"
void Scene::Draw2D()
{
	//シーンの更新処理
	mp_NowScene->Draw();

	//画面切り替えの更新処理
	if (m_isTransition)TransitionDraw();
}

void Scene::Update()
{
	//シーンの更新処理
	if (!m_isTransition)mp_NowScene->Update();

	//画面切り替えの更新処理
	if (m_isTransition)TransitionUpdate();
}

void Scene::Init()
{
	TransitionInit();

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

//===================================================================
// 画面切り替え処理
//===================================================================
//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え呼び出し処理
//+++++++++++++++++++++++++++++++++++++++++
void Scene::ChangeScene(c_SceneBase* next)
{
	if (m_isTransition)return;	//エラー防止

	//次のシーンを格納
	mp_NextScene = next;

	//画面切り替えの初期化処理
	m_isTransition = true;
	TransitionInit();
}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え初期化処理
//+++++++++++++++++++++++++++++++++++++++++
void Scene::TransitionInit()
{
	//フラグの初期化処理
	m_TransitionFlg = 0;

	m_ScreenAlpha = 0.0f;
	m_ScrennAdd = 0.03f;

}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え更新処理
//+++++++++++++++++++++++++++++++++++++++++
void Scene::TransitionUpdate()
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


		m_ScrennAdd *= -1;

		//フラグの進行処理
		m_TransitionFlg = 3;
		break;

	case 3:

		mp_NowScene->Update();

		m_ScreenAlpha += m_ScrennAdd;
		if (m_ScreenAlpha <= 0.0f) {
			//フラグ進行処理
			m_TransitionFlg = 4;
		}
		break;

	case 4:
		//現在のシーンの更新処理
		mp_NowScene->Update();

		//画面切り替え中かどうかを false に戻す
		m_isTransition = false;
		break;
	}
}

//+++++++++++++++++++++++++++++++++++++++++
// 画面切り替え描画処理
//+++++++++++++++++++++++++++++++++++++++++
void Scene::TransitionDraw()
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

