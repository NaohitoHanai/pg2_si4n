#include "Coin.h"

Coin::Coin()
{
}

Coin::Coin(const VECTOR& pos)
{
	position = pos;
}

Coin::~Coin()
{
}

void Coin::Update()
{
}

void Coin::Draw()
{
	DrawSphere3D(position + VGet(0, 50, 0), 30, 20,
		GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
}
