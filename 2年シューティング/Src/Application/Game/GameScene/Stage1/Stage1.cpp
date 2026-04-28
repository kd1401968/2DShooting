#include "Stage1.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/GameObject/Enemy/Ghost/Ghost.h"
void c_Stage1::Init()
{
	m_BackTex.Load("Texture/NightForest/Image without mist.png");
	m_Player = new c_Player;
	m_Player->Init();

	m_GameUI = new c_GameUI;
	m_GameUI->Init();

	m_BackPos = { 0.0f,0.0f };
	m_BackMoveX = 3;
}

void c_Stage1::Release()
{
	m_BackTex.Release();

	for (int i = 0; i < mp_Ghost.size(); i++) {
		delete mp_Ghost[i];
	}
	mp_Ghost.clear();

	delete m_Player;
	delete m_GameUI;
}

void c_Stage1::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->SetLife());

	if (rand() % 10 == 0) {
		Math::Vector2 GhostPos = { 640.0f+64.0f,(float)((rand() % 537)-238)};
		mp_Ghost.push_back(new c_Ghost(GhostPos));
	}

	for (int i = 0; i < mp_Ghost.size(); i++) {
		mp_Ghost[i]->Update();
	}

	for (auto it = mp_Ghost.begin(); it != mp_Ghost.end(); )
	{
		if (!(*it)->GetFlg())
		{
			delete* it;
			it = mp_Ghost.erase(it);
		}
		else
		{
			++it;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0);
	m_BackMat = S * T;
}

void c_Stage1::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	static float RectX = 0;
	RectX += m_BackMoveX;
	if (RectX <= -620) {
		RectX = 0;
	}
	Rect = { (int)RectX,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);

	for (int i = 0; i < mp_Ghost.size(); i++) {
		mp_Ghost[i]->Draw();
	}

	m_GameUI->Draw();

	m_Player->Draw();
}
