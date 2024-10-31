#include "Player.h"
#include "Stage.h"

Player::Player()
{
	collider = new SphereCollider();
	collider->offset = VGet(0, 50.0f, 0);
	collider->radius = 48.0f; // ï«Ç…à¯Ç¡Ç©Ç©ÇÁÇ»Ç¢ÇÊÇ§Ç…è¨Ç≥Çﬂ
}

Player::Player(const VECTOR& pos)
{
	position = pos;
	collider = new SphereCollider();
	collider->offset = VGet(0, 50.0f, 0);
	collider->radius = 48.0f; // ï«Ç…à¯Ç¡Ç©Ç©ÇÁÇ»Ç¢ÇÊÇ§Ç…è¨Ç≥Çﬂ
}

Player::~Player()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_W)) {
		position += VGet(0, 0, 2);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		position += VGet(-2, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		position += VGet(0, 0, -2);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		position += VGet(2, 0, 0);
	}
	Stage* st = FindGameObject<Stage>();
	position += st->CollisionSphere(position, collider);
}

void Player::Draw()
{
	DrawSphere3D(position + VGet(0, 50, 0),
		50.0f, 20, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}
