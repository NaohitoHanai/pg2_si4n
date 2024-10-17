#include "Bullet.h"
#include "Ground.h"

Bullet::Bullet()
{
}

Bullet::Bullet(VECTOR initPos, VECTOR initVel)
{
	position = initPos;
	velocity = initVel;
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	oldPosition = position;

	position += velocity;
	velocity.y -= Gravity;
	Ground* g = FindGameObject<Ground>();
	if (g->GetHeight(position) > position.y) {
		DestroyMe();
	}
}

void Bullet::Draw()
{
	DrawSphere3D(position, Radius, 20, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
