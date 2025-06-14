#include "Ball.h"
#include "config.h"
#include "BallManager.h"

Ball::Ball()
{
	hImage = LoadGraph("data/textures/billiyard.png");
	number = 1;
	position = VGet(100, 200, 0);
}

Ball::~Ball()
{
	// BallManager���玩�����폜
	BallManager* man = FindGameObject<BallManager>();
	man->DeleteBall(this);
	if (hImage > 0) {
		DeleteGraph(hImage);
	}
}

VECTOR wall[4] = {
	VGet(700, 400, 0),
	VGet(800, 500, 0),
	VGet(300, 600, 0),
	VGet(400, 500, 0),
};

void Ball::Update()
{
	position += velocity;
//	velocity *= 0.99f; // �K���Ȍ���
	static const float FRICTION = 0.1f; // ���C�ɂ�鑬�x�̌�����
	float cur = VSize(velocity); // ���̒���
	if (cur < FRICTION) {
		velocity = VGet(0, 0, 0);
	}
	else {
		cur -= FRICTION;
		velocity = VNorm(velocity) * cur;
	}

	// �O���̕ǂŔ���
	if (position.x < 32) { // ���̕�
		VECTOR dir = VGet(1, 0, 0); // �͂�^�������
		// �͂�^���钷�������߂�
		float len = VDot(velocity, dir);
		if (len < 0) {
			// �ǂ������x�N�g�������߂�
			VECTOR push = dir * len;
			// ��������A�ǂ������x�N�g��������
			velocity -= push;
			// �ǂ��牟���Ԃ����x�N�g����������
			velocity -= push;
		}
	}
	if (position.x > SCREEN_WIDTH-32) { // �E�̕�
		velocity.x *= -1.0f;
	}
	if (position.y < 32) { // ��̕�
		velocity.y *= -1.0f;
	}
	if (position.y > SCREEN_HEIGHT - 32) { // ���̕�
		velocity.y *= -1.0f;
	}

	for (int i = 0; i < 4; i++) {
		VECTOR w1 = wall[i];
		VECTOR w2 = wall[(i + 1) % 4];
		if (Segment_Point_MinLength(w1, w2, position) < 32) {
			VECTOR wall = w2 - w1;
			VECTOR n; // �@��
			n.x = -wall.y;
			n.y = wall.x;
			n.z = 0.0;
			n = VNorm(n) * -1.0f;
			float push = VDot(n, velocity);// �ǂ������͂̑傫���́A
			velocity -= n * push * 2.0f;
		}
	}
}

void Ball::Draw()
{
	int x = ((number - 1) % 4) * 64;
	int y = ((number - 1) / 4) * 64;
	DrawRectGraph(position.x-32, position.y-32,
		x, y, 64, 64, hImage, TRUE);
	for (int n = 0; n < 4; n++) {
		DrawLine(wall[n].x, wall[n].y, 
			wall[(n+1)%4].x, wall[(n + 1) % 4].y, GetColor(0, 255, 0));
	}
}
