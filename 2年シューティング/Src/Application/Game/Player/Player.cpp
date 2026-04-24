#pragma once
#include "Player.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
void c_Player::Init()
{
	m_Tex.Load("Texture/FLYING.png");
	m_AttackTex.Load("Texture/ATTACK.png");
	m_Alive = true;
	m_Life = 3;
	m_Pos = { 0.0f,30.0f };
	m_Speed = 5.0f;
	m_LR = -1;
	m_Rect = 0.0f;
	m_AttackRect = 0.0f;
	m_Interval = 0;
}
void c_Player::Update()
{
	if (m_Alive == 1) {
		//自機の移動
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
			m_Pos.x+= m_Speed;
			m_LR = -1;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
			m_Pos.x -= m_Speed;
			m_LR = 1;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
			m_Pos.y += m_Speed;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
			m_Pos.y -= m_Speed;
		}

		m_Rect += 0.13;
		if (m_Rect >= 4.0f) {
			m_Rect == 0.0f;
		}

		if (m_Interval == 0) {
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				mp_Bullet.push_back(new c_PBullet(m_Pos, m_LR));
				m_Interval = 32;
			}
		}

		if (m_Interval > 0) {
			if (m_Interval % 4 == 0)m_AttackRect += 1.0f;
			m_Interval--;
			if (m_Interval < 0)
			{
				m_Interval = 0;
				m_AttackRect = 0;
			}
		}

		c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
		if (game != nullptr) {
			if (game->GetNowSceneType() == GameSceneType::Start) {
				// スタート用の動き
				//m_Pos.x += 1;
			}
		}


	}

	for (int i = 0; i < mp_Bullet.size(); i++) {
		mp_Bullet[i]->Update();
	}

	for (auto it = mp_Bullet.begin(); it != mp_Bullet.end(); )
	{
		if (!(*it)->GetFlg())
		{
			delete* it;
			it = mp_Bullet.erase(it);
		}
		else
		{
			++it;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(1*m_LR, 1, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;
}
void c_Player::Draw()
{
	Math::Rectangle rect;
	Math::Color color;
	

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	if (m_Interval == 0) {
		rect = { (int)m_Rect * 79,0,79,69 };
		SHADER.m_spriteShader.DrawTex(&m_Tex, rect, 1.0f);
	}
	else {
		rect = { (int)m_AttackRect * 79,0,79,69 };
		SHADER.m_spriteShader.DrawTex(&m_AttackTex, rect, 1.0f);
	}

	for (int i = 0; i < mp_Bullet.size(); i++) {
		mp_Bullet[i]->Draw();
	}
}

void c_Player::Release()
{
	m_Tex.Release();

	for (int i = 0; i < mp_Bullet.size(); i++) {
		delete mp_Bullet[i];
	}
	mp_Bullet.clear();
}
