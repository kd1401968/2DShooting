#include "Mukade.h"

c_Mukade::c_Mukade(Math::Vector2 pos)
{
	bodyTex.Load("Texture/Mukade/karada.png");
	headTex.Load("Texture/Mukade/maruatama.png");
	leg2Tex.Load("Texture/Mukade/leg2.png");
	syokkakuTex.Load("Texture/Mukede/maruatama.png");
	kibaTex.Load("Texture/Mukade/kiba.png");


	//ムカデの初期化
	m_counst = 0;
	m_life = true;
	m_hflg = true;
	
	m_mkd.clear();//一度中身を綺麗にする
	m_angle.clear();
	m_pos.clear();
	int bodyNum = rand() % 5 + 5;//ムカデの体の数
	for (int i = 0;i < bodyNum;i++) 
	{
		//先頭データを保存する配列を生成
		int max = floorf(k_space / k_speed);
		for (int n = 0;n < max;n++)
		{
			m_angle.push_back(DirectX::XMConvertToRadians(180));
			m_pos.push_back(Math::Vector2(pos.x, pos.y));
		}

		//生成
		m_mkd.push_back
		(
			{
				Math::Vector2(pos.x,pos.y),
				Math::Vector2(k_speed,k_speed),
				Math::Matrix::Identity,
				DirectX::XMConvertToRadians(180),
				true,
				Math::Matrix::Identity
			}
		);
	}

}

c_Mukade::~c_Mukade()
{
	bodyTex.Release();
	headTex.Release();
	leg2Tex.Release();
	syokkakuTex.Release();
	kibaTex.Release();

	//空にする処理
	m_mkd.clear();
	m_angle.clear();
	m_pos.clear();
}

void c_Mukade::Update()
{
	//ムカデの進んだ距離を加算
	m_counst += 10;


	//ここからムカデ処理
	for (int Num = 0;Num < m_mkd.size();Num++) {

		if(Num==0)
		{
			//ムカデの頭の更新処理
			//保存座標と保存角度の更新(配列に挿入)
			m_angle.insert(m_angle.begin() + 1, m_angle[0]);
			m_pos.insert(m_pos.begin() + 1, m_pos[0]);

			

			//移動
			m_mkd[Num].pos.x = m_mkd[Num].pos.x + cosf(m_mkd[Num].angle) * m_mkd[Num].speed.x;
			m_mkd[Num].pos.y = m_mkd[Num].pos.y + sinf(m_mkd[Num].angle) * m_mkd[Num].speed.y;

			//保存角度と保存角度の格納と削除
			m_angle[0] = m_mkd[Num].angle;
			m_pos[0] = m_mkd[Num].pos;
			m_angle.pop_back();
			m_pos.pop_back();
		}
		
		//行列セットアップ
		int index = Num * floorf(k_space / k_speed);
		float angle = m_angle[index];
		float x = m_pos[index].x;
		float y = m_pos[index].y;
		
		//ムカデの触覚の更新処理
		if (Num == 0)
		{
			for (int ant = 0;ant < 2;ant++)
			{
				//触覚の左右
				enum type {
					right,
					left
				};

				//触覚の行列確定
				int LFTorRHT;
				float antAglDlt = static_cast<float>(rand() % 10 + 5);
				float antX, antY;
				float antAgl;
				float antAglAddR = DirectX::XMConvertToRadians((index * antAglDlt) + m_counst-60);
				float antAglAddL = DirectX::XMConvertToRadians((index * antAglDlt) + m_counst+60);
				antAglAddR = cosf(antAglAddR) * 15;
				antAglAddL = cosf(antAglAddL) * 15;
				switch (ant)
				{
				case right:
					LFTorRHT = 1;
					antAgl = angle + (DirectX::XMConvertToRadians(antAglAddR + 20) * LFTorRHT);
					antX = cosf(antAgl) * 30;
					antY = sinf(antAgl) * 30;
					break;

				case left:
					LFTorRHT = -1;
					antAgl = angle + (DirectX::XMConvertToRadians(antAglAddL + 20) * LFTorRHT);
					antX = cosf(antAgl) * 30;
					antY = sinf(antAgl) * 30;
					break;
				}
				Math::Matrix SSS = Math::Matrix::CreateScale(1, -1 * 1 * LFTorRHT, 1);
				Math::Matrix RRR = Math::Matrix::CreateRotationZ(antAgl);
				Math::Matrix TTT = Math::Matrix::CreateTranslation(x + antX, y + antY, 0);
				m_mkd[Num].leg1[ant] = SSS * RRR * TTT;
			}
		}

		float baseAngle = DirectX::XMConvertToRadians(180); // 左向き
		float shake = sinf(m_counst * 0.01f) * DirectX::XMConvertToRadians(10);
		m_mkd[0].angle = baseAngle + shake;

		//ムカデの体の更新処理
		if (Num != 0)
		{
			for (int leg = 0;leg < 2;leg++)
			{
				//足の左右
				enum type {
					right,
					left
				};

				//足の行列確定
				float legX, legY;
				float legAgl;
				float legAglAdd = DirectX::XMConvertToRadians((index * 6) + m_counst);
				legAglAdd = sinf(legAglAdd) * 15;
				switch (leg)
				{
				case right:
					legAgl = angle + DirectX::XMConvertToRadians(90 + legAglAdd);
					legX = cosf(legAgl) * 25;
					legY = sinf(legAgl) * 25;
					break;

				case left:
					legAgl = angle - DirectX::XMConvertToRadians(90 - legAglAdd);
					legX = cosf(legAgl) * 25;
					legY = sinf(legAgl) * 25;
					break;
				}
				Math::Matrix SS = Math::Matrix::CreateScale(2, 1.5, 1);
				Math::Matrix RR = Math::Matrix::CreateRotationZ(legAgl);
				Math::Matrix TT = Math::Matrix::CreateTranslation(x + legX, y + legY, 0);
				m_mkd[Num].leg1[leg] = SS * RR * TT;
			}
		}

		if (Num == m_mkd.size()-1) {
			for (int leg = 0;leg < 2;leg++)
			{
				//足の左右
				enum type {
					right,
					left
				};

				//曳航肢の行列確定
				int LFTorRHT;
				float legX, legY;
				float legAgl;
				float legAglAdd = DirectX::XMConvertToRadians((index * 5) + m_counst);
				legAglAdd = sinf(legAglAdd) * 2;
				switch (leg)
				{
				case right:
					LFTorRHT = 1;
					legAgl = angle + DirectX::XMConvertToRadians(170 + legAglAdd);
					legX = cosf(legAgl) * 30;
					legY = sinf(legAgl) * 30;
					break;

				case left:
					LFTorRHT = -1;
					legAgl = angle - DirectX::XMConvertToRadians(170 - legAglAdd);
					legX = cosf(legAgl) * 30;
					legY = sinf(legAgl) * 30;
					break;
				}
				Math::Matrix SE = Math::Matrix::CreateScale(4, 1.5 * LFTorRHT, 1);
				Math::Matrix RE = Math::Matrix::CreateRotationZ(legAgl);
				Math::Matrix TE = Math::Matrix::CreateTranslation(x + legX, y + legY, 0);
				m_mkd[Num].eik[leg] = SE * RE * TE;
			}
		}

		//行列確定
		Math::Matrix S = Math::Matrix::CreateScale(0.6, 1, 1);
		Math::Matrix R = Math::Matrix::CreateRotationZ(angle - DirectX::XMConvertToRadians(90));
		Math::Matrix T = Math::Matrix::CreateTranslation(x, y, 0);
		m_mkd[Num].matrix = S * R * T;

		//生存確認(パーツ単体)
		if (1500 < fabs(x) || 1000 < fabs(y))
		{
			m_mkd[Num].flg = false;
		}
		else
		{
			m_mkd[Num].flg = true;
		}
	}

	//生存確認(ムカデ自身)
	bool life = false;
	for(int i=0;i<m_mkd.size();i++)
	{
		if (m_mkd[i].flg)life = true;
	}
	if (!life)m_life = false;
}

void c_Mukade::Draw()
{
	//セットアップ
	Math::Color color;
	Math::Rectangle rect;

	//配列の後ろから描画していく
	for (int i = m_mkd.size() - 1; 0 <= i ;i--)
	{
		float delta = 1 + cosf(DirectX::XMConvertToRadians((i * 30) + m_counst)) * 0.3;
		float Cconst;

		if (i == 0) 
		{
			//牙
			color = { 1.2 , 1.2 , 1.2 ,1 };
			rect = { 0,0,84,86 };
			SHADER.m_spriteShader.SetMatrix(m_mkd[i].matrix);
			SHADER.m_spriteShader.DrawTex(&kibaTex, 0, 0, &rect, &color);

			//触覚
			Cconst = 0.9 * delta;
			color = { Cconst , Cconst , Cconst ,1 };
			rect = { 0,0,109,10 };
			for (int leg = 0;leg < 2;leg++) {
				SHADER.m_spriteShader.SetMatrix(m_mkd[i].leg1[leg]);
				SHADER.m_spriteShader.DrawTex(&syokkakuTex, 0, 0, &rect, &color);
			}

			//頭
			color = { 1.2 , 1.2 , 1.2 ,1 };
			rect = { 0,0,84,86 };
			SHADER.m_spriteShader.SetMatrix(m_mkd[i].matrix);
			SHADER.m_spriteShader.DrawTex(&headTex, 0, 0, &rect, &color);

		}
		else
		{

			//足
			Cconst = 0.9 * delta;
			color = { Cconst , Cconst , Cconst ,1 };
			rect = { 0,0,33,6 };
			for (int leg = 0;leg < 2;leg++) {
				SHADER.m_spriteShader.SetMatrix(m_mkd[i].leg1[leg]);
				SHADER.m_spriteShader.DrawTex(&leg2Tex, 0, 0, &rect, &color);
			}

			if (i == m_mkd.size()-1) {
				//足
				Cconst = 0.9 * delta;
				color = { Cconst , Cconst , Cconst ,1 };
				rect = { 0,0,33,6 };
				for (int leg = 0;leg < 2;leg++) {
					SHADER.m_spriteShader.SetMatrix(m_mkd[i].eik[leg]);
					SHADER.m_spriteShader.DrawTex(&leg2Tex, 0, 0, &rect, &color);
				}
			}

			//体
			Cconst = 1.5 * delta;
			color = { Cconst , Cconst , Cconst ,1 };
			rect = { 0,0,84,76 };
			SHADER.m_spriteShader.SetMatrix(m_mkd[i].matrix);
			SHADER.m_spriteShader.DrawTex(&bodyTex, 0, 0, &rect, &color);

		}

		/*SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
		SHADER.m_spriteShader.DrawBox(m_pos[i].x, m_pos[i].y, 10, 10, &color, true);*/
	}
	//AI確認用
	/*Math::Matrix matrix;
	color = { 1,1,1,1 };
	SHADER.m_spriteShader.SetMatrix(matrix);
	SHADER.m_spriteShader.DrawCircle(ai.x, ai.y, 10,&color, true);*/

	SHADER.m_spriteShader.SetMatrix(Math::Matrix::Identity);
	//SHADER.m_spriteShader.DrawBox(m_pos[0].x, m_pos[0].y, m_pos[m_pos.size()-1].x, m_pos[m_pos.size() - 1].y, &color, true);
	SHADER.m_spriteShader.DrawTriangle(m_pos[0].x, m_pos[0].y + 25, m_pos[0].x, m_pos[0].y - 25,
		m_pos[m_pos.size() - 1].x, m_pos[m_pos.size() - 1].y - 25, &color);
	SHADER.m_spriteShader.DrawTriangle(m_pos[0].x, m_pos[0].y + 25, m_pos[m_pos.size()-1].x, m_pos[m_pos.size()-1].y - 25,
		m_pos[m_pos.size() - 1].x, m_pos[m_pos.size() - 1].y + 25, &color);
}

