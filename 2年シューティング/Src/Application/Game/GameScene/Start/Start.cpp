#include "Start.h"
#include "Application/Game/Player/Player.h"
#include "Application/Game/GameUI/GameUI.h"
#include "Application/Game/GameScene/GameSceneBase.h"
#include "Application/Game/GameScene/Stage1/Stage1.h"
#include "Application/Game/Game.h"
#include "Application/Scene.h"
#include "Application/Game/GameObject/Bullet/PBullet/PBullet.h"
#include "Application/Game/GameObject/Explosion/Explosion.h"
void c_Start::Init(int PlayerLife,int Score)
{
	m_StartPos = { 0.0f,0.0f };

	m_BackTex.Load("Texture/Back.png");
	m_ChainTex.Load("Texture/chain.png");
	m_PlayerTex.Load("Texture/ATTACK.png");
	m_BulletTex.Load("Texture/FireBullet.png");
	m_SignTex.Load("Texture/kanban.png");
	m_PresonTex.Load("Texture/preson.png");
	m_KeyTex[0].Load("Texture/space.png");
	m_KeyTex[1].Load("Texture/key.png");
	m_ArrowTex.Load("Texture/arrow.png");
	m_Player = new c_Player(PlayerLife,m_StartPos);

	m_GameUI = new c_GameUI(PlayerLife,Score);

	m_BackPos = { 0.0f,0.0f };
	m_BackMoveX = 3;

	m_PlayerLife = PlayerLife;
	m_Score = Score;

	m_Cnt=3;

	m_InvFlg = false;

	for (int i = 0; i < 10; i++)
	{
		
        m_DeathPos[i] = { (float)(rand() % 1280 - 640), -250.0f };
		m_DeathRotate[i] = rand() % 181;
		m_DeathRect[i] = rand() % 8;
		if (rand() % 2 == 0)
		{
			m_LR[i] = 1;
		}
		else
		{
			m_LR[i] = -1;
		}
	}
	
}

void c_Start::Release()
{
	m_BackTex.Release();
	m_ChainTex.Release();
	m_PlayerTex.Release();
	m_BulletTex.Release();
	m_SignTex.Release();
	m_PresonTex.Release();
	m_KeyTex[0].Release();
	m_KeyTex[1].Release();
	m_ArrowTex.Release();

	for (int i = 0; i < mp_Explosion.size(); i++) {
		delete mp_Explosion[i];
	}
	mp_Explosion.clear();

	delete m_Player;
	delete m_GameUI;
}

void c_Start::Update()
{
	m_Player->Update();
	m_GameUI->Update(m_Player->GetLife());

	//テスト用
	//m_PlayerLife = 2;
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
		if (game) {
			game->ChangeGameScene(new c_Stage1(m_PlayerLife,m_Score));
		}

	}

	if (m_Player->GetPos().x>=700)
	{
		c_Game* game = dynamic_cast<c_Game*>(SCENE.GetNowScene());
		if (game) {
			game->ChangeGameScene(new c_Stage1(m_PlayerLife, m_Score));
		}

	}

	if (m_Cnt!=0)
	{
		if (m_Player->GetPos().x >= 38)
		{
			m_Player->SetPos({ 38,m_Player->GetPos().y });
		}
		if (m_Player->GetPos().x <= -37)
		{
			m_Player->SetPos({ -37,m_Player->GetPos().y });
		}
		if (m_Player->GetPos().y >= 36)
		{
			m_Player->SetPos({ m_Player->GetPos().x,36 });
		}
		if (m_Player->GetPos().y <= -36)
		{
			m_Player->SetPos({ m_Player->GetPos().x,-36 });
		}

		//プレイヤーの弾とボスのの当たり判定
		for (int i = 0; i < m_Player->mp_Bullet.size(); i++)
		{
			bool Hit = true;
			Math::Vector2 BulletPos = m_Player->mp_Bullet[i]->GetPos();
			Math::Vector2 PresonPos = { 0,0 };

			Hit = m_Hit.BulletHit(BulletPos, PresonPos, m_Player->mp_Bullet[i]->GetRadius(), { 169,155 });

			if (!Hit)
			{
				m_Player->SetBulletFlg(Hit, i);
				mp_Explosion.push_back(new c_Explosion());
				mp_Explosion.back()->Init(BulletPos,1.0f);
				m_Cnt--;
				if (m_Cnt <= 0)
				{
					mp_Explosion.push_back(new c_Explosion());
					mp_Explosion.back()->Init({0,70}, 6.0f);
					m_Player->SetNextFlg(false);
				}
				break;
			}
		}
	}
	else
	{
		if (!m_InvFlg)
		{
			m_ArrowAlpha += 0.005f;
			if (m_ArrowAlpha >= 0.5f)
			{
				m_ArrowAlpha = 0.5f;
				m_InvFlg = true;
			}
		}
		else
		{
			m_ArrowAlpha -= 0.005f;
			if (m_ArrowAlpha <= 0.0f)
			{
				m_ArrowAlpha = 0.0f;
				m_InvFlg = false;
			}
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

	S = Math::Matrix::CreateScale(0.5, 0.5, 1);
	T = Math::Matrix::CreateTranslation(0, 0, 0);
	m_PresonMat = S * T;

	for (int i = 0; i < 2; i++)
	{
		int LR = -1;
		if (i == 1)LR = 1;
		S = Math::Matrix::CreateScale(1.2, 1.7, 1);
		T = Math::Matrix::CreateTranslation(400*LR, 100, 0);
		m_SignMat[i] = S * T;
	}

	for (int i = 0; i < 3; i++)
	{
		float x;

		m_ChainRectY[i] = 500;
		switch (i)
		{
		case 0:
			m_ChainRectY[i] = 850;
			x = 0;
			break;
		case 1:
			x = 400;
			break;
		case 2:
			x = -400;
			break;
		default:
			break;
		}

		S = Math::Matrix::CreateScale(0.7, 0.7, 1);
		T = Math::Matrix::CreateTranslation(x, 360, 0);
		m_ChainMat[i] = S * T;
	}

	for (int i = 0; i < 2; i++)
	{
		int LR = -1;
		m_KeyRect[i] = {34,14};
		if (i == 1)
		{
			LR = 1;
			m_KeyRect[i] = { 47,31 };
		}
		S = Math::Matrix::CreateScale(1.8, 1.8, 1);
		T = Math::Matrix::CreateTranslation(400 *LR, 50, 0);
		m_KeyMat[i] = S * T;
	}

	for (int i = 0; i < 3; i++)
	{
		int LR = -1;
		float x, y;
		switch (i)
		{
		case 0:
			m_PlayerRectX[i] = 3;
			x = -430;
			y = 120;
			break;
		case 1:
			m_PlayerRectX[i] = 7;
			x = 360;
			y = 100;
			LR = 1;
			break;
		case 2:
			m_PlayerRectX[i] = 7;
			x = 440;
			y = 140;
			break;
		default:
			break;
		}
		S = Math::Matrix::CreateScale(0.8*LR, 0.8, 1);
		T = Math::Matrix::CreateTranslation(x, y, 0);
		m_PlayerMat[i] = S * T;
	}

	for (int i = 0; i < 10; i++)
	{
		S = Math::Matrix::CreateScale(0.8 * m_LR[i], 0.8, 1);
		R = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_DeathRotate[i]));
		T = Math::Matrix::CreateTranslation(m_DeathPos[i].x, m_DeathPos[i].y, 0);
		m_PlayerMat[i+3] = S * R * T;
	}

	S = Math::Matrix::CreateScale(0.8 , 0.8, 1);
	T = Math::Matrix::CreateTranslation(-370, 110, 0);
	m_BulletMat = S * T;

	S = Math::Matrix::CreateScale(0.8, 0.8, 1);
	T = Math::Matrix::CreateTranslation(550, -50, 0);
	m_ArrowMat = S * T;
}

void c_Start::Draw()
{
	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	rect = { 0,0,1280,720 };
	color = { 0.7f,0.7f,0.7f,1.0f };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, 0, 0, &rect, &color);

	m_GameUI->Draw();

	for (int i = 0; i < 3; i++)
	{
		rect = { 0,0,26,m_ChainRectY[i] };
		color = { 0.5f,0.4f,0.5f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_ChainMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_ChainTex, 0, 0, &rect, &color);
	}

	for (int i = 0; i < 2; i++)
	{
		rect = { 0,0,236,154 };
		color = { 1.0f,1.0f,1.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_SignMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_SignTex, 0, 0, &rect, &color);

		rect = { 0,0,(int)m_KeyRect[i].x,(int)m_KeyRect[i].y };
		color = { 1.0f,1.0f,1.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_KeyMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_KeyTex[i], 0, 0, &rect, &color);
	}

	for (int i = 0; i < 3; i++)
	{
		rect = { m_PlayerRectX[i]*79,0,79,69};
		color = { 1.0f,1.0f,1.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_PlayerMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_PlayerTex, 0, 0, &rect, &color);
	}
	for (int i = 0; i < 10; i++)
	{
		rect = { m_DeathRect[i] * 79,0,79,69 };
		color = { 0.8f,0.8f,0.8f,0.8f };
		SHADER.m_spriteShader.SetMatrix(m_PlayerMat[i+3]);
		SHADER.m_spriteShader.DrawTex(&m_PlayerTex, 0, 0, &rect, &color);
	}

	rect = { 0,0,64,64 };
	color = { 1.0f,1.0f,1.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(m_BulletMat);
	SHADER.m_spriteShader.DrawTex(&m_BulletTex, 0, 0, &rect, &color);

	m_Player->Draw();

	for (int i = 0; i < mp_Explosion.size(); i++) {
		mp_Explosion[i]->Draw();
	}

	if (m_Cnt >= 1)
	{
		rect = { 0,0,338,310 };
		color = { 1.0f,1.0f,1.0f,1.0f };
		SHADER.m_spriteShader.SetMatrix(m_PresonMat);
		SHADER.m_spriteShader.DrawTex(&m_PresonTex, 0, 0, &rect, &color);
	}
	else
	{
		rect = { 0,0,100,75 };
		color = { 1.0f,1.0f,1.0f,m_ArrowAlpha };
		SHADER.m_spriteShader.SetMatrix(m_ArrowMat);
		SHADER.m_spriteShader.DrawTex(&m_ArrowTex, 0, 0, &rect, &color);
	}
}
