#include "Boss.h"
#include "Application/Game/GameObject/Bullet/EBullet/Star/Star.h"
void c_Boss::Init()
{
	m_Tex.Load("Texture/Boss.png");

	m_Pos = { 1120.0f,0.0f };
	m_Scale = { 10.0f,8.0f };
	m_Radius = { 6.0f*m_Scale.x,20.0f*m_Scale.y };
	//m_Radius = { 80.0f, 64.0f };
	m_Life = 10;
	m_LR = -1;
	m_Rect = { 0,0 };
	m_Action = e_Action::StartAction;
	m_ShotFlg = false;
}

void c_Boss::Release()
{
	m_Tex.Release();

	for (int i = 0; i < mp_Star.size(); i++) {
		delete mp_Star[i];
	}
	mp_Star.clear();
}

void c_Boss::Update(Math::Vector2 Pos)
{
	switch (m_Action)
	{
	case e_Action::StartAction:
		m_Pos.x -= 3;
		if (m_Pos.x <= 420)
		{
			m_Pos.x = 420;
			m_Action = e_Action::ActionA;
		}
		break;
	case e_Action::ActionA:
		m_Rect.y = 2;
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
		if (m_Rect.x >= 8&&m_ShotFlg==false)
		{
			m_ShotFlg = true;
			for (int i = 0; i < 3; i++)
			{
				mp_Star.push_back(new c_Star({ m_Pos.x - 17 * m_Scale.x, m_Pos.y + 33 * m_Scale.y }, Pos));
			}
		}
		if (m_Rect.x >= 13)
		{
			m_Rect.x = 0;
			m_ShotFlg = false;
		}
    default:
		break;
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


	Math::Matrix S, R, T;
	S = Math::Matrix::CreateScale(m_Scale.x*m_LR, m_Scale.y, 1);
	T = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_Mat = S * T;
}

void c_Boss::Draw()
{
	Math::Rectangle rect = { (int)m_Rect.x * 160,((int)m_Rect.y * 128)+25,160,128 };
	Math::Color color = { 1.0f,1.0f,1.0f,1.0f };

	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, 0, -7, &rect, &color);

	/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(m_Pos.x-17*m_Scale.x, m_Pos.y+33*m_Scale.y, 10, 10, &color, true);*/

	for (int i = 0; i < mp_Star.size(); i++) {
		mp_Star[i]->Draw();
	}
}

void c_Boss::SetBossLife()
{
	m_Life--;
	if (m_Life <= 0)
	{
		m_Alive = false;
		m_Life = 0;
	}
}

