#pragma once
#include "../Library/GameObject.h"

class Ground : public GameObject
{
public:
	Ground();
	~Ground();
	void Draw() override;
private:
	int hModel;
};