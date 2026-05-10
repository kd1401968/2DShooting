#pragma once
#include "Player.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
void c_Player::Init(int Life, Math::Vector2 Pos)
{
	m_Tex.Load("Texture/FLYING.png");
	m_AttackTex.Load("Texture/ATTACK.png");
	m_Alive = true;
	m_Life = Life;
	m_Pos = Pos;
	m_Speed = { 6.0f,0.0f };
	m_LR = -1;
	m_Rect = 0.0f;
	m_AttackRect = 0.0f;
	m_Interval = 0;
	m_Count = 24;
	m_Radius = { 30.0f,25.0f };
	m_Alpha = 1.0f;
	m_InvFlg = false;
	m_StartFlg = false;
	m_NextFlg = false;
}
void c_Player::Update()
{
	/*c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
	if (game != nullptr)
	{
		if (game->GetNowSceneType() == GameSceneType::Start)
		{
			m_StartFlg = true;
		}

		if (game->GetNowSceneType() == GameSceneType::Stage1)
		{
			if (m_Pos.x <= -200&&m_StartFlg==false)
			{
				m_Pos.x += m_Speed.x;
			}
			else
			{
				m_StartFlg = true;
			}

			if (m_StartFlg)
			{
				if (m_NextFlg)
				{
					m_Speed.x = 6.0f;
					m_Pos.x += m_Speed.x;
				}
			}
		}

		if (game->GetNowSceneType() == GameSceneType::Stage2)
		{
			if (m_Pos.x <= 0 && m_StartFlg == false)
			{
				m_Pos.x += m_Speed.x;
			}
			else
			{
				m_StartFlg = true;
			}

		}
	}*/
	c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
	if (game == nullptr) return;

	GameSceneType type = game->GetNowSceneType();

	switch (type)
	{
	case GameSceneType::Start:
		m_StartFlg = true;
		break;

	case GameSceneType::Stage1:
		if (m_Pos.x <= -200 && m_StartFlg == false)
		{
			m_Pos.x += m_Speed.x;
		}
		else
		{
			m_StartFlg = true;
		}

		if (m_StartFlg && m_NextFlg)
		{
			m_Speed.x = 6.0f;
			m_Pos.x += m_Speed.x;
		}
		break;

	case GameSceneType::Stage2:
		if (m_Pos.x <= -400 && m_StartFlg == false)
		{
			m_Pos.x += m_Speed.x;
		}
		else
		{
			m_StartFlg = true;
		}
		break;
	}


	if (m_Alive)
	{
		m_Rect += 0.13;
		if (m_Rect >= 4.0f) {
			m_Rect = 0.0f;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(1 * m_LR, 1, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;

	if (!m_StartFlg) return;

	if (m_Alive == 1) {
		//自機の移動
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D') & 0x8000) {
			m_LR = -1;
			m_Speed.x = 1.0f;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A') & 0x8000) {
			m_Speed.x = -1.0f;
			m_LR = 1;
		}
		else
		{
			m_Speed.x = 0.0f;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W') & 0x8000) {
			m_Speed.y = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S') & 0x8000) {
			m_Speed.y = -1.0f;
		}
		else
		{
			m_Speed.y = 0.0f;
		}

		m_Speed.Normalize();

		m_Speed *= 6.0f;

		m_Pos += m_Speed;

		if (GetAsyncKeyState('G') & 0x8000)
		{
			m_InvFlg = true;
		}
		if(GetAsyncKeyState('H') & 0x8000)
		{
			m_InvFlg = false;
			m_Alpha = 1.0f;
		}
		if (m_InvFlg)
		{
			m_Alpha = 0.7f;
		}
		else
		{
			if (m_Alpha < 1.0f) m_Alpha += 0.01f;
			if (m_Alpha >= 1.0f) m_Alpha = 1.0f;
		}

		//画面外に出ないようにする
		if (!m_NextFlg)
		{
			if (m_Pos.x > (640 - m_Radius.x))	m_Pos.x = (640 - m_Radius.x);
		}
		if (m_Pos.x < (-640 + m_Radius.x))	m_Pos.x = (-640 + m_Radius.x);
		if (m_Pos.y > (360 - m_Radius.y))	m_Pos.y = (360 - m_Radius.y);
		if (m_Pos.y < ( - 280 + m_Radius.y))m_Pos.y = (-280 + m_Radius.y);

		//攻撃とインターバルの管理
		if (m_Interval == 0) {
			if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
				m_Interval++;
				m_AttackRect = 0;
			}
		}

		if (m_Count >=m_Interval && m_Interval >= 1)
		{
			int step = m_Count / 8;  // 8分割（m_Count が大きいほど step も大きくなる）

			// 次のフレームへ
			m_Interval++;

			if (step < m_Interval) {

				// アニメーション進行
				if (m_Interval % step == 0) {
					m_AttackRect++;
				}

				// ③ 弾を撃つタイミング（3/8）
				if (m_Interval == step * 3) {
					mp_Bullet.push_back(new c_PBullet(m_Pos, m_LR));
				}

				// ④ モーション終了 → リセット
				if (m_Interval >= m_Count) {
					m_Interval = 0;
					m_AttackRect = 0;
				}
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

	
}
void c_Player::Draw()
{
	if (m_Alive == 0) return;
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,m_Alpha };
	

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	if (m_Interval == 0) {
		rect = { (int)m_Rect * 79,0,79,69 };
		SHADER.m_spriteShader.DrawTex(&m_Tex, rect, color);
	}
	else {
		rect = { (int)m_AttackRect * 79,0,79,69 };
		SHADER.m_spriteShader.DrawTex(&m_AttackTex, rect, color);
	}

	for (int i = 0; i < mp_Bullet.size(); i++) {
		mp_Bullet[i]->Draw();
	}
}

void c_Player::SetBulletFlg(bool flg,int i)
{
	 mp_Bullet[i]->SetFlg(flg);
}

void c_Player::SetLife()
{
	if (m_InvFlg) return;

	if (m_Alpha >= 1.0f)
	{
		m_Alpha = 0.0f;
		m_Life--;
		if (m_Life <= 0)
		{
			m_Alive = false;
		}
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
