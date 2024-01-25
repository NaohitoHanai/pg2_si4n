#pragma once
// Goblin.h
#include "../Library/GameObject.h"

class Goblin : public GameObject
{
public:
	Goblin();
	~Goblin();
	void Update() override;
	void Draw() override;

	bool PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2);

	VECTOR Position() {
		return position;
	}
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};