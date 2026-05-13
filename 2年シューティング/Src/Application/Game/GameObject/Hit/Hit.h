#pragma once
class Hit
{
public:
	
	bool BulletHit(Math::Vector2 Apos, Math::Vector2 Bpos,
					Math::Vector2 Aradius,Math::Vector2 Bradius);
	bool BoxHit(Math::Vector2 Ppos, float Pradius,          // プレイヤー中心＋半径
		Math::Vector2 Fpos, Math::Vector2 Bpos  // 四角の左上・右下
	);
	bool BoxInHit(Math::Vector2 Ppos, Math::Vector2 Pradius,        // プレイヤー中心＋半径
		Math::Vector2 Bpos, Math::Vector2 Bradius  // 四角の左上・右下
	);
	bool PlayerHit(Math::Vector2 Playerpos, Math::Vector2 Enemypos,
					Math::Vector2 Playerradius, Math::Vector2 Enemyradius);
};