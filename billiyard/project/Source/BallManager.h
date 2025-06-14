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
//	static const int BallNum = 10; // �v���C���[�ʂ��P��
	std::vector<Ball*> balls;
	VECTOR shotDir; // �V���b�g�̌���

	float chargeLevel; //�`���[�W�� 0.0(0%)�`1.0(100%)
};