#include "Stage2.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/Effect/Rain/Rain.h"
#include "Application/Game/GameObject/Enemy/Boss/Boss.h"	
#include "Application/Game/GameObject/Hit/Hit.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
#include "Application/Game/GameObject/Explosion/Explosion.h"
#include "Application/Game/GameObject/Bullet/EBullet/Star/Star.h"
void c_Stage2::Init(int PlayerLife,int Score)
{
	m_StartPos = { -800.0f,0.0f };

	m_BackTex.Load("Texture/NightForest/Image without mist.png");
	m_RainTex.Load("Texture/rain.png");

	m_Player = new c_Player(PlayerLife, m_StartPos);

	m_GameUI = new c_GameUI(PlayerLife,Score);

	m_BackPos = { 0.0f,0.0f };

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

	for (int i = 0; i < m_Rain.size(); i++)
	{
		m_Rain[i]->Update();
	}

	if (m_Player->GetPos().x + m_Player->GetRadius().x >= m_Boss->GetPos().x)
	{
		m_Player->SetPos({ m_Boss->GetPos().x-m_Player->GetRadius().x,m_Player->GetPos().y});
	}

	HitDec2();

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

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(2.07, 2, 1);
	T = Math::Matrix::CreateTranslation(m_BackPos.x, m_BackPos.y, 0);
	m_BackMat = S * T;
}

void c_Stage2::Draw()
{
	Math::Rectangle Rect;
	Math::Color color = { 0.7f,0.7f,0.7f,1.0f };

	Rect = { 0,0,620,360 };
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &Rect, &color);

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
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(BulletPos);
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
			mp_Explosion.back()->Init(PlayerPos);
		}

		if (PlayerPos.x >= BossPos.x)
		{
			m_Player->SetPos({ BossPos.x , PlayerPos.y });
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
			mp_Explosion.back()->Init(PlayerPos);
			m_Boss->mp_Star[i]->SetFlg(Hit);
			break;
		}
	}
}
