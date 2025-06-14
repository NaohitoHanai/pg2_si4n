#include "BallManager.h"
#include "Ball.h"
#include "Pocket.h"

namespace {
	static const float CHARGE_MAX_TIME = 0.5f; // �`���[�WMAX�܂ł̎���
	static const float CHARGE_MAX_POWER = 4.0f; // �`���[�W�ő厞�̈З�
	static const RECT GAUGE = { 100, 400, 120, 600 }; // �Q�[�W�̕\���ꏊ�i���A��A�E�A���j
};

BallManager::BallManager()
{
	Ball* my = Instantiate<Ball>();
	my->number = 16; // MY_NUMBER�ƒ�`���Ƃ�����
	my->position = VGet(200, 100, 0);
	balls.push_back(my);

	for (int i = 1; i <= 9; i++) {
		Ball* target = Instantiate <Ball>();
		target->number = i;
		target->position = VGet(100 * i, 180, 0);
		balls.push_back(target);
	}

	shotDir = VGet(1, 0, 0); // ���˂�������i�x�N�g���j
}

BallManager::~BallManager()
{
}

void BallManager::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		//shotDir���E�ɏ������񂷂�
		shotDir *= MGetRotZ(DegToRad(3.0f));
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		//shotDir�����ɏ������񂷂�
		shotDir *= MGetRotZ(DegToRad(-3.0f));
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		balls[0]->velocity += shotDir * 2.0f;
	}
	for (int b1 = 0; b1 < balls.size(); b1++) {
		balls[b1]->addPower = VGet(0, 0, 0); // addPower���N���A
	}
	for (int b1 = 0; b1 < balls.size(); b1++) {
		for (int b2 = b1+1; b2 < balls.size(); b2++) {
			VECTOR pDiff = balls[b2]->position - balls[b1]->position;
			if (VSize(pDiff) < 64) {
				// �n�����x�̌���
				VECTOR dir = VNorm(pDiff); // �͂�^�������
				float len = VDot(balls[b1]->velocity, dir);
				if (len > 0) {
					balls[b2]->addPower += dir * len;
					balls[b1]->addPower -= dir * len;
				}
				dir *= -1;
				len = VDot(balls[b2]->velocity, dir);
				if (len > 0) {
					balls[b1]->addPower += dir * len;
					balls[b2]->addPower -= dir * len;
				}
			}
		}
	}
	for (int b1 = 0; b1 < balls.size(); b1++) {
		balls[b1]->velocity += balls[b1]->addPower;
	}

	// �e�{�[�����|�P�b�g�ɓ����������ׂ�
	Pocket* pocket = FindGameObject<Pocket>();
	for (auto itr = balls.begin(); itr != balls.end(); itr++) {
		if (pocket->BallIn((*itr)->position, 32)) { // �|�P�b�g�ɓ�������
			(*itr)->DestroyMe(); // ball���g���폜
		}
	}
}

void BallManager::Draw()
{
	VECTOR p1 = balls[0]->position;
	VECTOR p2 = shotDir * 100 + balls[0]->position;
	DrawLine(p1.x, p1.y, p2.x, p2.y, GetColor(255, 0, 0));

	DrawBox(GAUGE.left, GAUGE.top, GAUGE.right, GAUGE.bottom, GetColor(255, 255, 255), FALSE);
}

void BallManager::DeleteBall(Ball* ball)
{
	for (auto itr = balls.begin(); itr != balls.end(); ) {
		if (*itr == ball) {
			itr = balls.erase(itr);
		}
		else {
			itr++;
		}
	}
}
