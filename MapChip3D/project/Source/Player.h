#pragma once
#include "../Library/GameObject.h"
#include "SphereCollider.h"
class Player : public GameObject {
public:
	Player();
	Player(const VECTOR& pos);
	~Player();
	void Update() override;
	void Draw() override;
	const VECTOR& Position() {
		return position;
	}
private:
	VECTOR position;
	SphereCollider* collider;
};