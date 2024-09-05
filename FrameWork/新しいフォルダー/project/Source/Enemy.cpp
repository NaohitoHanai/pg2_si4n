#include "Enemy.h"

Enemy::Enemy()
{
	hImage = LoadGraph("data/enemy01.png");
	position = VGet(600, 100, 0);
	timer = 0;
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	timer++;
}

void Enemy::Draw()
{
	int y = (timer / 6) % 5;
	DrawRectGraph(position.x, position.y,
		4, y*36+2, 32, 32, hImage, TRUE);
}
