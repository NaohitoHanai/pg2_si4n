#include "Pocket.h"

Pocket::Pocket()
{
	position = VGet(0, 0, 0);
	radius = 100.0f;
}

Pocket::~Pocket()
{
}

void Pocket::Draw()
{
	DrawCircle(position.x, position.y, radius, GetColor(64, 64, 64), TRUE);
}

bool Pocket::BallIn(VECTOR bPos, float bRadius)
{
	float distance = VSize(position - bPos);
	if (distance + bRadius < radius) {
		return true;
	}
	return false;
}
