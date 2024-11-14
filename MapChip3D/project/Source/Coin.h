#pragma once
#include "../Library/GameObject.h"
class Coin : public GameObject {
public:
	Coin();
	Coin(const VECTOR& pos);
	~Coin();
	void Update() override;
	void Draw() override;
	const VECTOR& Position() {
		return position;
	}
private:
	VECTOR position;
	float height;
	float velocity;
	float rotation;
	int hModel;
	bool got;
	float gotTimer;
};