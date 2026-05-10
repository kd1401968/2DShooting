#include "Rain.h"

void c_Rain::Release()
{
}

//初期化
void c_Rain::Init(KdTexture& tex)
{
	m_Kazamuki = 5;

	m_pTexture = &tex;

	m_Pos.x = (rand() % 1660) - 830 + 32 + m_Kazamuki * 15;
	m_Pos.y = (rand() % 720 + 360) + 32;
	m_Move.x = 0;
	m_Move.y = (-(rand() % 5)) - 10;
	//0.3から0.7を求める
	m_Size = { 0.5,0.3f + (0.7f - 0.3f) * Rnd() };
	m_Rotate = rand() % m_Kazamuki;
	m_Color = { 1,1,1,0.3f + (0.5f - 0.3f) * Rnd() };
	m_TexSize = 64;

}

//更新
void c_Rain::Update()
{

	//座標確定
	m_Pos.y += m_Move.y;
	m_Pos.x += m_Move.x - m_Kazamuki / 3;

	//一定の高さで切り取り範囲を縮める
	if (m_Pos.y <= (rand() % 10) * -1 - 250)
	{
		m_TexSize += (int)m_Move.y;
		if (m_TexSize <= 0) {
			m_TexSize = 0;
		}
	}

	//雨粒リスポーン
	if (m_TexSize == 0)
	{
		m_Pos.y = 360 + 32 + m_Kazamuki * 15;
		m_Pos.x = (rand() % 1660) - 830 + 32 + m_Kazamuki * 15;
		m_Rotate = rand() % m_Kazamuki;
		m_Size = { 0.5,0.3f + (0.7f - 0.3f) * Rnd() };
		m_Color = { 1,1,1,0.3f + (0.5f - 0.3f) * Rnd() };
		m_TexSize = 64;
	}


	//行列作成
	Math::Matrix transMat, scaleMat, rotateMat;
	scaleMat = Math::Matrix::CreateScale(m_Size.x, m_Size.y, 1);
	rotateMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_Rotate * -1));
	transMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);

	m_Matrix = scaleMat * rotateMat * transMat;

}

//描画
void c_Rain::Draw()
{
	//行列をセットする
	SHADER.m_spriteShader.SetMatrix(m_Matrix);
	//描画
	Math::Rectangle srcRect = { 0,0,32,m_TexSize };	//テクスチャ座標
	//Math::Color color = { 1.0f,1.0f,1.0f,1.0f };//色RGBA
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, &srcRect, &m_Color);
}



float c_Rain::Rnd()
{
	return rand() / (float)RAND_MAX;
}
