#include "Eye.h"
#include "Application/Game/GameObject/Bullet/EBullet/IceBullet/IceBullet.h"
void c_Eye::Init(float x, float y, float scale)
{
	Eye1Tex.Load("Texture/Eye/Eye10.png");
	Eye2Tex.Load("Texture/Eye/Eye6.png");
	Eye3Tex.Load("Texture/Eye/Eye4.png");

	m_Pos[0] = { x,y };
	m_Scale = scale;
	m_Rotate = 0;
	m_RotateDelta = 0;
	m_Alpha = 0;
	m_Count = 0;
	m_Flg = true;
	m_MoveFlg = true;
}



void c_Eye::Update(float tX, float tY)
{
	//ターゲットの座標から距離を求める
	float disx =tX - m_Pos[0].x;
	float disy = tY - m_Pos[0].y;

	float distance = sqrt(disx * disx + disy * disy);

	//一定の距離に入ると出現し離れると消える
	if (distance <= 600) {
		m_Alpha += 0.05;
		if (m_Alpha >= 1)m_Alpha = 1;
		if (distance <= 400)
			m_Alpha -= 0.08;
		if (m_Alpha <= 0)m_Alpha = 0;
	}
	else {
		m_Alpha -= 0.05;
		if (m_Alpha <= 0)
		{
			m_RotateDelta = 0;
			m_Alpha = 0;
		}
	}

	//フラグがtrueの場合近づくと消える
	if (m_Invisible == true) {
		if (distance <= 200) {
			m_Alpha -= 0.08;
			if (m_Alpha <= 0)m_Alpha = 0;
		}
	}

	if (m_MoveFlg == true)
	{
		m_Pos[0].x -= 6;
		if (m_Pos[0].x <= 550.0f&&m_Count==0)
		{
			m_MoveFlg = false;
		}
	}
	else {
		m_Count++;
		m_Alpha = 1.0f;
		if (m_Count == 30)m_IceBullet = new c_IceBullet(m_Pos[0], { tX,tY }, m_Scale);
		if (m_Count >= 60)
		{
			m_MoveFlg = true;
		}
	}

	if (m_IceBullet)
	{
		m_IceBullet->Update();
	}
	

	if (m_Pos[0].x <= -680)m_Flg = false;


	if (m_Alpha <= 0)return;

	//座標から角度を求める

	float dx = tX - m_Pos[0].x;
	float dy = tY - m_Pos[0].y;

	// atan2で角度を計算（ラジアン）
	float targetRotate = DirectX::XMConvertToDegrees(atan2f(dy, dx));
	m_RotateDelta = (targetRotate - m_Rotate) * 0.1 + m_RotateDelta * 0.8;
	m_Rotate += m_RotateDelta;

	//行列確定
	Math::Matrix S, R, T;

	//目
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	T = Math::Matrix::CreateTranslation(m_Pos[0].x, m_Pos[0].y, 0);
	Eye1Mat = S * T;

	float x, y;

	//第二の目の位置調整
	//黒目の後ろのやつ
	float tyousei = 8 * m_Scale;

	//角度調整
	m_Pos[1].x = x = m_Pos[0].x + 76 * m_Scale * cosf(DirectX::XMConvertToRadians(m_Rotate));
	m_Pos[1].y = y = m_Pos[0].y + 80 * m_Scale * sinf(DirectX::XMConvertToRadians(m_Rotate));
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	T = Math::Matrix::CreateTranslation(m_Pos[1].x, m_Pos[1].y - tyousei, 0);
	Eye2Mat = S * T;

	float burex, burey;

	//黒目を震えさせる
	burex = (rand() % 6 - 3)  * m_Scale;
	burey = (rand() % 6 - 3) * m_Scale;


	//角度調整
	m_Pos[2].x = x = m_Pos[1].x + 60 * m_Scale * cosf(DirectX::XMConvertToRadians(m_Rotate));
	m_Pos[2].y = y = m_Pos[1].y + 60 * m_Scale * sinf(DirectX::XMConvertToRadians(m_Rotate));

	//黒目
	S = Math::Matrix::CreateScale(m_Scale, m_Scale, 1);
	T = Math::Matrix::CreateTranslation(m_Pos[2].x + burex, m_Pos[2].y + burey, 0);
	Eye3Mat = S * T;
}

void c_Eye::Draw()
{
	Math::Rectangle rect;
	Math::Color color;

	color = { 1.5,1.5,1.5,m_Alpha };

	//目
	rect = { 0,0,456,489 };
	SHADER.m_spriteShader.SetMatrix(Eye1Mat);
	SHADER.m_spriteShader.DrawTex(&Eye1Tex, 0, 0, &rect, &color);

	color = { 1,1,1,m_Alpha };
	//黒目の後ろのやつ
	rect = { 0,0,311,316 };
	SHADER.m_spriteShader.SetMatrix(Eye2Mat);
	SHADER.m_spriteShader.DrawTex(&Eye2Tex, 0, 0, &rect, &color);


	if (m_IceBullet)
	{
		m_IceBullet->Draw();
	}


	//黒目
	rect = { 0,0,185,179 };
	SHADER.m_spriteShader.SetMatrix(Eye3Mat);
	SHADER.m_spriteShader.DrawTex(&Eye3Tex, 0, 0, &rect, &color);
}

void c_Eye::Release()
{
	Eye1Tex.Release();
	Eye2Tex.Release();
	Eye3Tex.Release();

	delete m_IceBullet;
}
