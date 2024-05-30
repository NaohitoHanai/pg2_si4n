#pragma once
#include "../Library/GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR position; // カメラ座標
	VECTOR rotation; // カメラ操作用の回転
	VECTOR target; // 注視点
};