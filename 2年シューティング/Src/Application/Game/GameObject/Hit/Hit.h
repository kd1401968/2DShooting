#pragma once
class Hit
{
public:
	
	bool BulletHit(Math::Vector2 Apos, Math::Vector2 Bpos,
					Math::Vector2 Aradius,Math::Vector2 Bradius);
	bool PlayerHit(Math::Vector2 Playerpos, Math::Vector2 Enemypos,
					Math::Vector2 Playerradius, Math::Vector2 Enemyradius);
};