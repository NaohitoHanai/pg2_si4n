#include "Zap.h"

Zap::Zap() : Zap(VGet(600, 100, 0))
{
}

Zap::Zap(VECTOR pos)
{
	hImage = LoadGraph("data/bullet.png");
	position = pos;
}

Zap::~Zap()
{
}

void Zap::Update()
{
	position.y -= 5.0f;
	if (position.y < -32.0f) {
		DestroyMe();
	}
}

void Zap::Draw()
{
	DrawRectGraph(position.x, position.y,
		32, 0, 32, 32, hImage, TRUE);
}
