#pragma once
#include "../Library/GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
	const VECTOR& Direction() const {
		return direction;
	}
	const VECTOR& Position() const {
		return position;
	}
private:
	VECTOR position; // カメラ座標
	VECTOR rotation; // カメラ操作用の回転
	VECTOR target; // 注視点
	VECTOR direction; // カメラの向いている方向の単位ベクトル
};