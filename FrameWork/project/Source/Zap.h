#pragma once
#include "../Library/GameObject.h"

class Zap : public GameObject {
public:
	Zap();
	Zap(VECTOR pos);
	~Zap();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	VECTOR position;
};