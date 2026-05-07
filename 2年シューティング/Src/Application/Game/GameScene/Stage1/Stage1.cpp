#include "Stage1.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/GameObject/Enemy/Ghost/Ghost.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
#include "Application/Game/GameObject/Explosion/Explosion.h"
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
	m_GameUI->Update(m_Player->GetLife());

	if (rand() % 10 == 0) {
		Math::Vector2 GhostPos = { 640.0f+64.0f,(float)((rand() % 537)-238)};
		mp_Ghost.push_back(new c_Ghost(GhostPos));
	}

	for (int i = 0; i < m_Player->mp_Bullet.size(); i++)
	{
		bool Hit=true;
		for (int j = 0; j < mp_Ghost.size(); j++)
		{
			Math::Vector2 BulletPos = m_Player->mp_Bullet[i]->GetPos();
			Math::Vector2 GhostPos = mp_Ghost[j]->GetPos();

			Hit=m_Hit.BulletHit(BulletPos, GhostPos, m_Player->mp_Bullet[i]->GetRadius(), mp_Ghost[j]->GetRadius());

			if (!Hit)
			{
				m_Player->SetBulletFlg(Hit, i);
				mp_Ghost[j]->SetFlg(Hit);
				mp_Explosion.push_back(new c_Explosion());
				mp_Explosion.back()->Init(GhostPos);
				break;
			}
		}
		if (!Hit)continue;
	}

	for (int i = 0; i < mp_Ghost.size(); i++)
	{
		bool Hit = true;
		Math::Vector2 PlayerPos = m_Player->GetPos();
		Math::Vector2 GhostPos = mp_Ghost[i]->GetPos();

		Hit = m_Hit.BulletHit(PlayerPos, GhostPos, m_Player->GetRadius(), mp_Ghost[i]->GetRadius());

		if (!Hit)
		{
			m_Player->SetLife();
			mp_Ghost[i]->SetFlg(Hit);
			mp_Explosion.push_back(new c_Explosion());
			mp_Explosion.back()->Init(GhostPos);
			break;
		}
		if (!Hit)continue;
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

	for (int i = 0; i < mp_Explosion.size(); i++) {
		mp_Explosion[i]->Draw();
	}

	m_GameUI->Draw();

	m_Player->Draw();
}
