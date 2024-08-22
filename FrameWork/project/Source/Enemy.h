#pragma once
#include "../Library/GameObject.h"

class Enemy : public GameObject {
public:
	Enemy();
	~Enemy();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	VECTOR position;
	int timer;
};