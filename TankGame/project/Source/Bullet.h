#pragma once
#include "../Library/GameObject.h"

class Bullet : public GameObject {
public:
	Bullet();
	Bullet(VECTOR initPos, VECTOR initVel);
	~Bullet();
	void Update();
	void Draw();
	static constexpr float Gravity = 0.3f;
	static constexpr float Radius = 20.0f;
	const VECTOR& Position() const {
		return position;
	}
	const VECTOR& OldPosition() const {
		return oldPosition;
	}

private:
	VECTOR oldPosition;
	VECTOR position;
	VECTOR velocity;
};