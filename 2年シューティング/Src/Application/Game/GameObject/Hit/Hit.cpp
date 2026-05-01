#include "Hit.h"

bool Hit::BulletHit(Math::Vector2 Apos, Math::Vector2 Bpos, Math::Vector2 Aradius, Math::Vector2 Bradius)
{
	float x, y;

	x = Apos.x - Bpos.x;
	y = Apos.y - Bpos.y;

	float dis = sqrtf(x * x + y * y);

	if (Aradius.x + Bradius.x >= dis)
	{
		return false;
	}
	else
	{
		return true;
	}
}
