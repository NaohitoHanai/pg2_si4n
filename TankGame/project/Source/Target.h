#pragma once
#include "../Library/GameObject.h"

class Target : public GameObject {
public:
	Target();
	Target(VECTOR pos);
	~Target();
	void Update();
	void Draw();
private:
	int hModel;
	VECTOR position;
};