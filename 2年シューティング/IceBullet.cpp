#include "IceBullet.h"


void c_IceBullet::Init(Math::Vector2 pos, float scale)
{
	m_Tex.Load("Texture/IceBullet.png");
	m_Scale = scale;
	m_Pos = pos;
	m_Speed = { 0.0f,0.0f };
	m_Flg = true;
}
void c_IceBullet::Update()
{
}

void c_IceBullet::Draw()
{
}

void c_IceBullet::Release()
{
}
