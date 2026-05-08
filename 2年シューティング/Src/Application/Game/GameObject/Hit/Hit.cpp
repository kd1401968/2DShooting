#include "Hit.h"

bool Hit::BulletHit(Math::Vector2 Apos, Math::Vector2 Bpos, Math::Vector2 Aradius, Math::Vector2 Bradius)
{

	float dx = fabs(Apos.x - Bpos.x);
	float dy = fabs(Apos.y - Bpos.y);

	float rx = Aradius.x + Bradius.x;
	float ry = Aradius.y + Bradius.y;


	if (dx <= rx && dy <= ry)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Hit::PlayerHit(Math::Vector2 Playerpos, Math::Vector2 Enemypos, Math::Vector2 Playerradius, Math::Vector2 Enemyradius)
{

	return false;
}
