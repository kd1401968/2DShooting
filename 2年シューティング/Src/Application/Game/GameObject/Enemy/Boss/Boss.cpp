#include "Boss.h"
#include "Application/Game/GameObject/Bullet/EBullet/Star/Star.h"
#include "Application/Game/GameObject/Bullet/EBullet/Mukade/Mukade.h"
#include "Application/Game/GameObject/Enemy/BigGhost/BigGhost.h"
#include "Application/Game/GameObject/Bullet/EBullet/Spider/Spider.h"
void c_Boss::Init()
{
	m_Tex.Load("Texture/Boss.png");
	m_GateTex.Load("Texture/Gate.png");

	m_Pos = { 1120.0f,0.0f };
	m_Scale = { 10.0f,8.0f };
	m_Radius = { 6.0f * m_Scale.x,20.0f * m_Scale.y };
	//m_Radius = { 80.0f, 64.0f };
	m_Life = 25;
	m_LR = -1;
	m_UD = false;
	m_Rect = { 0,0 };
	m_Action = e_Action::StartAction;
	m_ShotFlg = false;

	m_GatePos[0] = { 540,55 };
	m_GateScale.x = 15;
	m_GRectX = 0;

	m_DeathFlg = false;

	mp_BigGhost.push_back(new c_BigGhost({ 900,0 }));
	m_LastFlg = false;

	m_Alpha = 0.5f;

	mp_Spider.push_back(new c_Spider());
}

void c_Boss::Release()
{
	m_Tex.Release();
	m_GateTex.Release();

	for (int i = 0; i < mp_Star.size(); i++) {
		delete mp_Star[i];
	}
	mp_Star.clear();

	for (int i = 0; i < mp_Mukade.size(); i++) {
		delete mp_Mukade[i];
	}
	mp_Mukade.clear();

	for (int i = 0; i < mp_Spider.size(); i++) {
		delete mp_Spider[i];
	}
	mp_Spider.clear();

	for (int i = 0; i < mp_BigGhost.size(); i++) {
		delete mp_BigGhost[i];
	}
	mp_BigGhost.clear();
}

void c_Boss::Update(Math::Vector2 Pos)
{

	if (m_Action == e_Action::EndAction)
	{
		for (int i = 0; i < mp_Star.size(); i++) {
			delete mp_Star[i];
		}
		mp_Star.clear();

		for (int i = 0; i < mp_Mukade.size(); i++) {
			delete mp_Mukade[i];
		}
		mp_Mukade.clear();
	}

	static bool Death = false;
	if (m_Action == e_Action::Death)
	{
		Death = true;
	}
	if (Death == true)
	{
		for (int i = 0; i < mp_BigGhost.size(); i++)
		{
			mp_BigGhost[i]->EndFlg();
		}
	}

	if (m_Action == e_Action::EndAction)return;

	switch (m_Action)
	{
	case e_Action::StartAction:
		m_Pos.x -= 3;
		if (m_Pos.x <= 420)
		{
			m_Pos.x = 420;
			m_Alpha = 1.0f;
			m_Action = e_Action::ActionA;
		}
		break;
	case e_Action::ActionA:
		m_Rect.y = 2;
		if (m_Life <= 12)
		{
			m_Action = e_Action::ActionB;
		}
		break;
	case e_Action::ActionB:
		for (int i = 0; i < mp_Star.size(); i++) {
			delete mp_Star[i];
		}
		mp_Star.clear();
		m_Rect.y = 0;
		m_Alpha = 0.5f;
		m_Pos.x += 3;
		if (m_Pos.x >= 870)
		{
			m_Pos.x = -870;
			m_LR = 1;
			m_ShotFlg = false;
			m_Action = e_Action::ActionC;
		}
		break;
	case e_Action::ActionC:
		m_Pos.x += 3;
		if (m_Pos.x >= -430)
		{
			m_LastFlg = true;
			m_Pos.x = -430;
			m_Alpha = 1.0f;
			m_Rect.y = 2;
		}
		break;
	case e_Action::Death:

		m_Rect.y = 6;
		//m_Pos.x = 421;
		break;
	default:
		break;
	}


	m_Rect.x += 0.18f;

	switch ((int)m_Rect.y)
	{
	case 0:
		if (m_Rect.x >= 8)
		{
			m_Rect.x = 0;
		}
		break;
	case 2:
		if (m_LastFlg == false)
		{
			if (m_Rect.x >= 8 && m_ShotFlg == false)
			{
				m_ShotFlg = true;
				for (int i = 0; i < 2; i++)
				{
					mp_Star.push_back(new c_Star({ m_Pos.x - 17 * m_Scale.x, m_Pos.y + 33 * m_Scale.y }, Pos));
				}
				if (rand() % 3 == 0)
				{
					mp_Mukade.push_back(new c_Mukade({ 640.0f + 64.0f, (float)((rand() % 537) - 238) }));
				}
			}
			if (m_Rect.x >= 13)
			{
				m_Rect.x = 0;
				m_Action = e_Action::StartAction;
				m_ShotFlg = false;
			}
		}
		else
		{
			if (m_Rect.x >= 8 && m_ShotFlg == false)
			{
			}
			if (m_Rect.x >= 13)
			{
				m_Rect.x = 0;

				if (rand() % 3 == 0)
				{
					for (int i = 0; i < mp_BigGhost.size(); i++)
					{
						mp_BigGhost[i]->GoGhost();
					}
				}
				m_ShotFlg = false;
			}
		}
		break;
	case 6:
		if (m_Rect.x >= 9)
		{
			m_Rect.x = 9;
			m_Action = e_Action::EndAction;
			m_DeathFlg = true;
		}
		break;
	default:
		break;
	}

	if (m_LastFlg == true)
	{
		if (m_UD)
		{
			m_Pos.y += 3;
			if (m_Pos.y >= 200)
			{
				m_UD = false;
			}
		}
		else
		{
			m_Pos.y -= 3;
			if (m_Pos.y <= -100)
			{
				m_UD = true;
			}
		}
	}


	for (int i = 0; i < mp_Star.size(); i++) {
		mp_Star[i]->Update();
	}

	for (auto it = mp_Star.begin(); it != mp_Star.end(); )
	{
		if (!(*it)->GetFlg())
		{
			delete* it;
			it = mp_Star.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (int i = 0; i < mp_Mukade.size(); i++) {
		mp_Mukade[i]->Update();
	}

	for (auto it = mp_Mukade.begin(); it != mp_Mukade.end(); )
	{
		if (!(*it)->GetMukadeLife())
		{
			delete* it;
			it = mp_Mukade.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (m_LastFlg == true)
	{

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
	}
	for (int i = 0; i < mp_Spider.size(); i++) {
		mp_Spider[i]->Update();
	}

	for (auto it = mp_Spider.begin(); it != mp_Spider.end(); )
	{
		if (!(*it)->GetFlg())
		{
			delete* it;
			it = mp_Spider.erase(it);
		}
		else
		{
			++it;
		}
	}

	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale.x * m_LR, m_Scale.y, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;

	m_GRectX += 0.5f;
	if (m_GRectX >= 8)
	{
		m_GRectX = 0;
	}
	S = Math::Matrix::CreateScale(m_GateScale.x * m_LR, m_GateScale.x, 1);
	T = Math::Matrix::CreateTranslation(m_GatePos[0].x + 220, m_GatePos[0].y, 0);
	m_GateMat[0] = S * T;

	S = Math::Matrix::CreateScale(m_GateScale.x * m_LR, m_GateScale.x, 1);
	T = Math::Matrix::CreateTranslation(m_GatePos[0].x - 240, m_GatePos[0].y, 0);
	m_GateMat[1] = S * T;
}

void c_Boss::Draw()
{
	if (m_Action == e_Action::EndAction)return;

	Math::Rectangle rect;
	Math::Color color = { 1.0f,1.0f,1.0f,m_Alpha };

	if (m_Pos.x == 420)
	{

		rect = { ((int)m_GRectX * 64) + 32, 0, 32, 64 };
		SHADER.m_spriteShader.SetMatrix(m_GateMat[1]);
		SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);

		for (int i = 0; i < mp_Mukade.size(); i++) {
			mp_Mukade[i]->Draw();
		}

		rect = { (int)m_GRectX * 64, 0, 32, 64 };
		SHADER.m_spriteShader.SetMatrix(m_GateMat[0]);
		SHADER.m_spriteShader.DrawTex(&m_GateTex, 0, 0, &rect, &color);
	}


	rect = { (int)m_Rect.x * 160,((int)m_Rect.y * 128) + 25,160,128 };
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, 0, -7, &rect, &color);

	/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(m_Pos.x-17*m_Scale.x, m_Pos.y+33*m_Scale.y, 10, 10, &color, true);*/

	for (int i = 0; i < mp_Star.size(); i++) {
		mp_Star[i]->Draw();
	}

	for (int i = 0; i < mp_Spider.size(); i++) {
		mp_Spider[i]->Draw();
	}

	if (m_LastFlg)
	{
		for (int i = 0; i < mp_BigGhost.size(); i++) {
			mp_BigGhost[i]->Draw();
		}
	}
}

void c_Boss::SetBossLife()
{
	if (m_Action == e_Action::Death)return;

	m_Life--;
	if (m_Life == 0)
	{
		m_Action = e_Action::Death;
		m_Rect.x = 0;
		//m_Life = 0;
	}
}

