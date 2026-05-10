#pragma once

//パーティクル
class c_Rain
{
public:
	c_Rain(KdTexture& tex) { Init(tex); }
	~c_Rain() {Release();};

	
	void Update();
	void Draw();


	//風の強さ
	int m_Kazamuki;

	//0.0～1.0の乱数を求める関数
	float Rnd();

private:

	void Init(KdTexture& tex);
	void Release();

	Math::Vector2 m_Pos;	//座標
	Math::Vector2 m_Move;	//移動量
	Math::Vector2 m_Size;	//サイズ
	Math::Color   m_Color;	//色
	int			  m_Lifesapn;//有効時間(活動限界時間)
	bool		  m_BRepeat;//繰り返しフラグ
	Math::Matrix  m_Matrix; //行列
	int  m_Rotate;			//回転量
	KdTexture* m_pTexture;  //テクスチャ(アドレス)
	int			  m_TexSize;//切り取り範囲

};
