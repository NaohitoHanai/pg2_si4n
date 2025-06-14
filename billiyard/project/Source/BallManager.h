#pragma once
//BallManager.h
#include "../Library/gameObject.h"
#include "Ball.h"
#include <vector>

class BallManager : public GameObject {
public:
	BallManager();
	~BallManager();
	void Update();
	void Draw();

	void DeleteBall(Ball* ball);
private:
//	static const int BallNum = 10; // プレイヤー玉が１つ
	std::vector<Ball*> balls;
	VECTOR shotDir; // ショットの向き

	float chargeLevel; //チャージ量 0.0(0%)～1.0(100%)
};