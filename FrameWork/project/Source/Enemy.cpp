#include "Enemy.h"
#include "Zap.h"
#include "../Library/ObjectManager.h"

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
	auto zaps = ObjectManager::GetInst()->FindGameObjects<Zap>();
	for (Zap* zap : zaps)  {
		VECTOR zPos = zap->Position();
		if (VSize(VSub(zPos, position)) < 32) {
			zap->DestroyMe();
			position.y -= 5;
		}
	}
	timer++;
}

void Enemy::Draw()
{
	int y = (timer / 6) % 5;
	DrawRectGraph(position.x, position.y,
		4, y*36+2, 32, 32, hImage, TRUE);
}
