#pragma once
#include "../Library/GameObject.h"

class Maze : public GameObject {
public:
	Maze();
	~Maze();
	void Update() override;
	void Draw() override;
};