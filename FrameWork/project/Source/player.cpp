#include "player.h"
#include "Zap.h"

Player::Player()
{
	hImage = LoadGraph("data/solvalou.png");
	position = VGet(600, 600, 0);
}

Player::~Player()
{
	if (hImage >= 0) {
		DeleteGraph(hImage);
	}
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_W))
		position.y -= 1.0f;
	if (CheckHitKey(KEY_INPUT_S))
		position.y += 1.0f;
	if (CheckHitKey(KEY_INPUT_D))
		position.x += 1.0f;
	if (CheckHitKey(KEY_INPUT_A))
		position.x -= 1.0f;
//	if (CheckHitKey(KEY_INPUT_SPACE)) {
//		new Zap(position);
	}
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y,
		0, 0, 32, 32, hImage, TRUE);
}
