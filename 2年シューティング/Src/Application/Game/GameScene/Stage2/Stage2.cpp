#include "Stage2.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/Effect/Rain/Rain.h"
#include "Application/Game/GameObject/Enemy/Boss/Boss.h"	
#include "Application/Game/GameObject/Hit/Hit.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
#include "Application/Game/GameObject/Explosion/Explosion.h"
#include "Application/Game/GameObject/Bullet/EBullet/Star/Star.h"
#include "Application/Game/GameObject/Bullet/EBullet/Mukade/Mukade.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
#include"Application/Result/Result.h"
#include "Application/Title/Title.h"
void c_Stage2::Init(int PlayerLife, int Score)
{
	m_StartPos = { -800.0f,0.0f };

	m_BackTex.Load("Texture/NightForest/Image(1).png");
	m_RainTex.Load("Texture/rain.png");

	m_Player = new c_Player(PlayerLife, m_StartPos);

	m_GameUI = new c_GameUI(PlayerLife,Score);

	m_BackPos[0] = { 0,0 };
	m_BackPos[1] = { 1280,0 };

	m_StartFlg = false;

	m_Boss = new c_Boss();

	m_RainNum = 60;

	for (int i = 0; i < m_RainNum; i++)
	{
		m_Rain.push_back(new c_Rain(m_RainTex));
	}

}
void c_Stage2::Release()
{
	m_BackTex.Release();
	m_RainTex.Release();

	for (int i = 0; i < m_Rain.size(); i++)
	{
		delete m_Rain[i];
	}

	for (int i = 0; i < mp_Explosion.size(); i++) {
		delete mp_Explosion[i];
	}
	mp_Explosion.clear();

	delete m_Player;
	delete m_GameUI;
	delete m_Boss;
}
void c_Stage2::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	m_Boss->Update(m_Player->GetPos());

	if (m_Player->GetLife() == 0)
	{
		static int Count = 0;
		Count++;
		if (Count >= 120)
		{
			SCENE.ChangeScene(new c_Result(m_GameUI->GetScore(), false));
		}
	}

	for (int i = 0; i < m_Rain.size(); i++)
	{
		m_Rain[i]->Update();
	}

	if (m_Boss->GetLast())
	{
		for (int i = 0; i < m_Rain.size(); i++)
		{
			m_Rain[i]->m_Kazamuki++;
			if (m_Rain[i]->m_Kazamuki >= 20)
			{
				m_Rain[i]->m_Kazamuki = 20;
			}
		}

		for (int i = m_Rain.size(); i < 180; i++)
		{
			m_Rain.push_back(new c_Rain(m_RainTex));
		}
	}

	if (m_Player->GetPos().x >= 700)
	{
		SCENE.ChangeScene(new c_Result(m_GameUI->GetScore(),true));
	}

	HitDec2();

	if (m_Boss->GetLife()==0)
	{
		static int cnt = 0;
		cnt++;
		if (cnt % 2 == 0)
		{
			if (cnt <= 60)
			{
				Math::Vector2 bossPos = m_Boss->GetPos();

				float rx = (rand() % 100) - 50;
				float ry = (rand() % 100) - 50;

				Math::Vector2 expPos = { bossPos.x + rx, bossPos.y + ry };


				mp_Explosion.push_back(new c_Explosion());
				mp_Explosion.back()->Init(expPos,1.0f);
			}
		}
	}
	else
	{
		if(m_Boss->GetLast())
		{
			if (m_Player->GetPos().x - m_Player->GetRadius().x <= m_Boss->GetPos().x)
			{
				m_Player->SetPos({ m_Boss->GetPos().x + m_Player->GetRadius().x,m_Player->GetPos().y });
			}
		}
	}

	if (m_Player->GetStartFlg())
	{
		for (int i = 0; i < mp_Explosion.size(); i++) {
			mp_Explosion[i]->Update();
		}

		for (auto it = mp_Explosion.begin(); it != mp_Explosion.end(); )
		{
			if (!(*it)->GetFlg())
			{
				delete* it;
				it = mp_Explosion.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_BackPos[i].x -= 0.0f;
		if (m_BackPos[i].x <= -1280)
		{
			m_BackPos[i].x = 1280;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2.6, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos[0].x, m_BackPos[0].y, 0);
	m_BackMat[0] = S * T;

	S = Math::Matrix::CreateScale(2.09 * -1, 2.6, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos[1].x, m_BackPos[1].y, 0);
	m_BackMat[1] = S * T;
}

void c_Stage2::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 0.7f,0.7f,0.7f,1.0f };

	for (int i = 0; i < 2; i++)
	{
		rect = { 0,0,620,360 };
		SHADER.m_spriteShader.SetMatrix(m_BackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);
	}

	m_Boss->Draw();

	if (m_Player->GetStartFlg())
	{
		for (int i = 0; i < mp_Explosion.size(); i++) {
			mp_Explosion[i]->Draw();
		}
	}

	m_Player->Draw();

	for (int i = 0; i < m_Rain.size(); i++)
	{
		m_Rain[i]->Draw();
	}

	m_GameUI->Draw();

}

void c_Stage2::HitDec2()
{
	static bool alreadyDone = false; // 一度だけ実行するためのフラグ

	bool nowEnd = m_Boss->GetDeath();

	if (!alreadyDone && nowEnd)
	{
		// ★ここが一回だけ実行される処理
		m_GameUI->SetScore(50000);
		m_Player->SetNextFlg(true);

		alreadyDone = true; // 二度と入らないようにする
	}

	// ★ここより下の処理は、alreadyDone が true なら全部スキップ
	if (alreadyDone)
	{
		return; // ここで関数を抜ける
	}

	if (m_Boss->GetAlpha() < 1.0f)return;

	//プレイヤーの弾とボスのの当たり判定
	for (int i = 0; i < m_Player->mp_Bullet.size(); i++)
	{
		bool Hit = true;
		Math::Vector2 BulletPos = m_Player->mp_Bullet[i]->GetPos();
		Math::Vector2 BossPos = m_Boss->GetPos();

		Hit = m_Hit.BulletHit(BulletPos, BossPos, m_Player->mp_Bullet[i]->GetRadius(), m_Boss->GetRadius());

		if (!Hit)
		{
			m_Player->SetBulletFlg(Hit, i);
			m_GameUI->SetScore(200);
			m_Boss->SetBossLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(BulletPos, 1.0f);
			break;
		}
	}

	{
		bool Hit = true;
		Math::Vector2 BossPos = m_Boss->GetPos();
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Hit = m_Hit.BulletHit(BossPos, PlayerPos, m_Boss->GetRadius(), m_Player->GetRadius());
		if (!Hit && m_Player->GetAlpha() >= 1.0f)
		{
			m_Player->SetLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(PlayerPos, 1.0f);
		}

		if (!m_Boss->GetLast())
		{
			if (PlayerPos.x >= BossPos.x)
			{
				m_Player->SetPos({ BossPos.x , PlayerPos.y });
			}
		}
		else
		{
			if (PlayerPos.x <= BossPos.x)
			{
				m_Player->SetPos({ BossPos.x , PlayerPos.y });
			}
		}
	}


	for (int i = 0; i < m_Boss->mp_Star.size(); i++)
	{
		bool Hit = true;
		Math::Vector2 EyePos = m_Boss->mp_Star[i]->GetPos();
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Hit = m_Hit.BulletHit(EyePos, PlayerPos, m_Boss->mp_Star[i]->GetRadius(), m_Player->GetRadius());
		if (!Hit && m_Player->GetAlpha() >= 1.0f)
		{
			m_Player->SetLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(PlayerPos, 1.0f);
			m_Boss->mp_Star[i]->SetFlg(Hit);
			break;
		}
	}

	for (int i = 0; i < m_Boss->mp_Mukade.size(); i++)
	{
		Math::Vector2 Fpos = m_Boss->mp_Mukade[i]->GetHitBoxFront();
		Math::Vector2 Bpos = m_Boss->mp_Mukade[i]->GetHitBoxBack();

		Math::Vector2 PlayerPos = m_Player->GetPos();
		float PlayerRadius = m_Player->GetRadius().x;

		bool hit = m_Hit.BoxHit(PlayerPos, PlayerRadius, Fpos, Bpos);

		if (hit && m_Player->GetAlpha() >= 1.0f)
		{
			m_Player->SetLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(PlayerPos, 1.0f);
			break;
		}
	}

}
