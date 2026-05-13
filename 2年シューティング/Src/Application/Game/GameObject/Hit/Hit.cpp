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

bool Hit::BoxHit(Math::Vector2 Ppos, float Pradius, Math::Vector2 Fpos, Math::Vector2 Bpos)
{
	// ‰~‚Ì’†S‚ðŽlŠp‚Ì”ÍˆÍ‚ÉƒNƒ‰ƒ“ƒviÅ‚à‹ß‚¢“_‚ð‹‚ß‚éj
	float closestX = std::max(Fpos.x, std::min(Ppos.x, Bpos.x));
	float closestY = std::max(Fpos.y, std::min(Ppos.y, Bpos.y));

	// ‰~‚Ì’†S‚ÆŽlŠp‚ÌÅÚ‹ß“_‚Ì‹——£
	float dx = Ppos.x - closestX;
	float dy = Ppos.y - closestY;

	// ‹——£‚ª”¼ŒaˆÈ‰º‚È‚ç“–‚½‚è
	return (dx * dx + dy * dy) <= (Pradius * Pradius);

}

bool Hit::BoxInHit(Math::Vector2 Ppos, Math::Vector2 Pradius, Math::Vector2 Bpos, Math::Vector2 Bradius)
{

	Math::Vector4 pos;
	pos.x = Ppos.x + Pradius.x;
	pos.z = Ppos.x - Pradius.x;
	pos.y = Ppos.y + Pradius.y;
	pos.w = Ppos.y - Pradius.y;
	Math::Vector4 box;
	box.x = Bpos.x + Bradius.x;
	box.z = Bpos.x - Bradius.x;
	box.y = Bpos.y + Bradius.y;
	box.w = Bpos.y - Bradius.y;

	if (pos.x <= box.x && pos.z >= box.z && pos.y <= box.y && pos.w >= box.w)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

bool Hit::PlayerHit(Math::Vector2 Playerpos, Math::Vector2 Enemypos, Math::Vector2 Playerradius, Math::Vector2 Enemyradius)
{

	return false;
}
