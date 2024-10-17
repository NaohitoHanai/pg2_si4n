#pragma once
#include "../Library/GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(VECTOR initPos, VECTOR initVel);
	~Bullet();
	void Update();
	void Draw();
private:
	VECTOR position;
	VECTOR velocity;
};