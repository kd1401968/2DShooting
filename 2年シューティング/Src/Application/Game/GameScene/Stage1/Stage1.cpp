#include "Stage1.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/GameObject/Enemy/Ghost/Ghost.h"
#include "Application/Game/GameObject/Enemy/BigGhost/BigGhost.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
#include "Application/Game/GameObject/Explosion/Explosion.h"
#include "Application/Game/GameObject/Enemy/Eye/Eye.h"
#include "Application/Game/GameObject/Bullet/EBullet/IceBullet/IceBullet.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
#include "Application/Game/GameScene/Stage2/Stage2.h"
#include "Application/Result/Result.h"
void c_Stage1::Init(int PlayerLife,int Score)
{
	m_StartPos = { -800.0f,0.0f };

	m_BackTex.Load("Texture/NightForest/Image(1).png");
	m_Player = new c_Player(PlayerLife,m_StartPos);
	
	m_GameUI = new c_GameUI(PlayerLife,Score);

	m_BackPos[0] = { 0,0 };
	m_BackPos[1] = { 1280,0 };
	m_BackMoveX = 3;

	mp_BigGhost.push_back(new c_BigGhost({ -1100.0f ,0.0f }));


	m_Cnt = 0;
	m_Intarval = 0;
}

void c_Stage1::Release()
{
	m_BackTex.Release();

	for (int i = 0; i < mp_Ghost.size(); i++) {
		delete mp_Ghost[i];
	}
	mp_Ghost.clear();

	for (int i = 0; i < mp_BigGhost.size(); i++) {
		delete mp_BigGhost[i];
	}
	mp_BigGhost.clear();

	for (int i = 0; i < mp_Eye.size(); i++) {
		delete mp_Eye[i];
	}
	mp_Eye.clear();

	for (int i = 0; i < mp_Explosion.size(); i++) {
		delete mp_Explosion[i];
	}
	mp_Explosion.clear();

	delete m_Player;
	delete m_GameUI;
}

void c_Stage1::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	if (m_Player->GetLife() == 0)
	{
		static int Count = 0;
		Count++;
		if (Count >= 120)
		{
			SCENE.ChangeScene(new c_Result(m_GameUI->GetScore(), false));
		}
	}

	if (m_Player->GetStartFlg()) {

		if (m_Cnt >= 23)
		{
			mp_BigGhost[0]->EndFlg();

			m_Intarval++;
			if(m_Intarval >= 120)
			{
				m_Player->SetNextFlg(true);
				if (m_Player->GetPos().x >= 700.0f)
				{
					c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
					if (game) {
						game->ChangeGameScene(new c_Stage2(m_Player->GetLife(),m_GameUI->GetScore()));
					}
				}
			}
		}
		else
		{
			if (rand() % 30 == 0)
			{
				Math::Vector2 GhostPos = { 640.0f + 64.0f,(float)((rand() % 537) - 238) };
				mp_Ghost.push_back(new c_Ghost(GhostPos));
			}
			if (rand() % 45 == 0)
			{
				mp_Eye.push_back(new c_Eye(640.0f + 64.0f, (float)((rand() % 537) - 238), (rand() % 101 + 80) / 1000.0f));
			}
		}

		HitDec();

		for (int i = 0; i < mp_BigGhost.size(); i++) {
			mp_BigGhost[i]->Update();
		}

		for (auto it = mp_BigGhost.begin(); it != mp_BigGhost.end(); )
		{
			if (!(*it)->GetFlg())
			{
				delete* it;
				it = mp_BigGhost.erase(it);
			}
			else
			{
				++it;
			}
		}

		for (int i = 0; i < mp_Ghost.size(); i++) {
			mp_Ghost[i]->Update();
		}

		for (int i = 0; i < mp_Eye.size(); i++) {
			mp_Eye[i]->Update(m_Player->GetPos().x, m_Player->GetPos().y);
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

		for (auto it = mp_Eye.begin(); it != mp_Eye.end(); )
		{
			if (!(*it)->GetFlg())
			{
				delete* it;
				it = mp_Eye.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		m_BackPos[i].x -= 3.2f;
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

void c_Stage1::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	for (int i = 0; i < 2; i++)
	{
		rect = { 0,0,620,360 };
		SHADER.m_spriteShader.SetMatrix(m_BackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);
	}

	if (m_Player->GetStartFlg())
	{

		for (int i = 0; i < mp_Ghost.size(); i++) {
			mp_Ghost[i]->Draw();
		}


		for (int i = 0; i < mp_Eye.size(); i++) {
			mp_Eye[i]->Draw();
		}

		for (int i = 0; i < mp_BigGhost.size(); i++) {
			mp_BigGhost[i]->Draw();
		}


		for (int i = 0; i < mp_Explosion.size(); i++) {
			mp_Explosion[i]->Draw();
		}
	}

	m_GameUI->Draw();

	m_Player->Draw();
}



void c_Stage1::HitDec()
{
	if (!m_Player->GetAlive()) return;

	//プレイヤーとゴーストの当たり判定
	for (int i = 0; i < mp_Ghost.size(); i++)
	{
		bool Hit = true;
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Math::Vector2 GhostPos = mp_Ghost[i]->GetPos();

		Hit = m_Hit.BulletHit(PlayerPos, GhostPos, m_Player->GetRadius(), mp_Ghost[i]->GetRadius());

		if (!Hit)
		{
			if (m_Player->GetAlpha() >= 1.0f) {
				m_Player->SetLife();
			}
			mp_Ghost[i]->SetFlg(Hit);
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(GhostPos, 1.0f);
			break;
		}
		if (!Hit)continue;
	}

	//プレイヤーの弾とゴーストの当たり判定
	for (int i = 0; i < m_Player->mp_Bullet.size(); i++)
	{
		bool Hit = true;
		for (int j = 0; j < mp_Ghost.size(); j++)
		{
			Math::Vector2 BulletPos = m_Player->mp_Bullet[i]->GetPos();
			Math::Vector2 GhostPos = mp_Ghost[j]->GetPos();

			Hit = m_Hit.BulletHit(BulletPos, GhostPos, m_Player->mp_Bullet[i]->GetRadius(), mp_Ghost[j]->GetRadius());

			if (!Hit)
			{
				m_Player->SetBulletFlg(Hit, i);
				mp_Ghost[j]->SetFlg(Hit);
				m_GameUI->SetScore(100);
				mp_Explosion.push_back(new c_Explosion());
				mp_Explosion.back()->Init(GhostPos, 1.0f);
				m_Cnt += 1;
				break;
			}
		}
		if (!Hit)continue;
	}

	//ビッグゴーストとゴーストの当たり判定
	for (int i = 0; i < mp_Ghost.size(); i++)
	{
		Math::Vector2 BigGhostPos = mp_BigGhost[0]->GetPos();
		Math::Vector2 GhostPos = mp_Ghost[i]->GetPos();
		if (BigGhostPos.x > GhostPos.x)
		{
			mp_BigGhost[0]->GoGhost();
			bool Alive = false;
			mp_Ghost[i]->SetFlg(Alive);
		}
	}


	//プレイヤーとビッグゴーストの当たり判定
	{
		bool Hit = true;
		Math::Vector2 BigGhostPos = mp_BigGhost[0]->GetPos();
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Hit = m_Hit.BulletHit(BigGhostPos, PlayerPos, mp_BigGhost[0]->GetRadius(), m_Player->GetRadius());
		if (!Hit && m_Player->GetAlpha() >= 1.0f)
		{
			m_Player->SetLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(PlayerPos, 1.0f);
		}

		if (PlayerPos.x <= BigGhostPos.x)
		{
			m_Player->SetPos({ BigGhostPos.x , PlayerPos.y });
		}
	}

	//プレイヤーの弾とビッグゴーストの当たり判定
	for (int i = 0; i < m_Player->mp_Bullet.size(); i++)
	{
		bool Hit = true;
		Math::Vector2 BulletPos = m_Player->mp_Bullet[i]->GetPos();
		Math::Vector2 GhostPos = mp_BigGhost[0]->GetPos();

		Hit = m_Hit.BulletHit(BulletPos, GhostPos, m_Player->mp_Bullet[i]->GetRadius(), mp_BigGhost[0]->GetRadius());

		if (!Hit)
		{
			m_Player->SetBulletFlg(Hit, i);
			mp_BigGhost[0]->BackGhost();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(BulletPos, 1.0f);
			break;
		}
	}

	for(int i=0;i<mp_Eye.size();i++)
	{
		if (!mp_Eye[i]->m_IceBullet)continue;
		bool Hit = true;
		Math::Vector2 EyePos = mp_Eye[i]->m_IceBullet->GetPos();
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Hit = m_Hit.BulletHit(EyePos, PlayerPos, mp_Eye[i]->m_IceBullet->GetRadius(), m_Player->GetRadius());
		if (!Hit && m_Player->GetAlpha() >= 1.0f)
		{
			m_Player->SetLife();
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(PlayerPos, 1.0f);
			mp_Eye[i]->m_IceBullet->SetFlg(Hit);
			break;
		}
	}
}
