#pragma once
#include "../Library/GameObject.h"
#include <vector>

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR position;
	VECTOR lookAt;
	std::vector<VECTOR> lastPos;
};