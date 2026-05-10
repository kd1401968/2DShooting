#pragma once

class c_Mukade
{
public:

	c_Mukade(Math::Vector2 pos);	//コンストラクタ
	~c_Mukade();	//デストラクタ

	//+++++++++++++++++++++++++++++++++++++++++
	// 外部から参照可能
	//+++++++++++++++++++++++++++++++++++++++++
	void Update();	//更新処理
	void Draw();	//描画処理

	//生か死
	const bool GetMukadeLife() const { return(m_life); }


	Math::Vector2 GetHitBoxFront()
	{
		Math::Vector2 head = m_pos[0];
		Math::Vector2 tail = m_pos[m_pos.size() - 1];

		float margin = 25.0f; // 体の太さに合わせて調整

		Math::Vector2 Fpos;
		Fpos.x = std::min(head.x, tail.x) - margin;
		Fpos.y = std::min(head.y, tail.y) - margin;

		return Fpos;
	}

	Math::Vector2 GetHitBoxBack()
	{
		Math::Vector2 head = m_pos[0];
		Math::Vector2 tail = m_pos[m_pos.size() - 1];

		float margin = 25.0f;

		Math::Vector2 Bpos;
		Bpos.x = std::max(head.x, tail.x) + margin;
		Bpos.y = std::max(head.y, tail.y) + margin;

		return Bpos;
	}


private:

	//基本の構造体
	struct s_Sprite {
		Math::Vector2 pos;
		Math::Vector2 speed;
		Math::Matrix matrix;
		float angle;		//角度
		bool flg;

		//足追加
		Math::Matrix leg1[2];
		//曳航肢
		Math::Matrix eik[2];
	};

	//定数
	static constexpr float k_space = 48.0f;
	static constexpr float k_speed = 8.0f;

	//制御
	std::vector<float>m_angle;		//保存角度
	std::vector<Math::Vector2>m_pos;	//保存座標
	std::vector<s_Sprite> m_mkd;		//ムカデ

	KdTexture bodyTex;				//体
	KdTexture headTex;				//頭
	KdTexture leg2Tex;				//足２
	KdTexture syokkakuTex;				//触覚
	KdTexture kibaTex;				//触覚

	bool m_life;						//フラグ
	bool m_hflg;						//ホーミングフラグ
	bool m_kiomi;						//ホーミングフラグ
	float m_counst;					//ムカデの進んだ距離
};