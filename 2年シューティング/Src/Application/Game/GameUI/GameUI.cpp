#include "Application/Game/GameUI/GameUI.h"
void c_GameUI::Init() 
{

}
void c_GameUI::Update(int i)
{

}
void c_GameUI::Draw()
{
	Math::Color color = { 0.0f,0.0f,0.0f,1.0f };
	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	SHADER.m_spriteShader.DrawBox(0, -320, 640, 40, &color, true);
}
void c_GameUI::Release()
{

}