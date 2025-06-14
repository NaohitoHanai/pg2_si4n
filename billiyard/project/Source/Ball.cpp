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
	// BallManagerから自分を削除
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
//	velocity *= 0.99f; // 適当な減速
	static const float FRICTION = 0.1f; // 摩擦による速度の減少量
	float cur = VSize(velocity); // 今の長さ
	if (cur < FRICTION) {
		velocity = VGet(0, 0, 0);
	}
	else {
		cur -= FRICTION;
		velocity = VNorm(velocity) * cur;
	}

	// 外周の壁で反射
	if (position.x < 32) { // 左の壁
		VECTOR dir = VGet(1, 0, 0); // 力を与える向き
		// 力を与える長さを求める
		float len = VDot(velocity, dir);
		if (len < 0) {
			// 壁を押すベクトルを求める
			VECTOR push = dir * len;
			// 自分から、壁を押すベクトルを引く
			velocity -= push;
			// 壁から押し返されるベクトルを加える
			velocity -= push;
		}
	}
	if (position.x > SCREEN_WIDTH-32) { // 右の壁
		velocity.x *= -1.0f;
	}
	if (position.y < 32) { // 上の壁
		velocity.y *= -1.0f;
	}
	if (position.y > SCREEN_HEIGHT - 32) { // 下の壁
		velocity.y *= -1.0f;
	}

	for (int i = 0; i < 4; i++) {
		VECTOR w1 = wall[i];
		VECTOR w2 = wall[(i + 1) % 4];
		if (Segment_Point_MinLength(w1, w2, position) < 32) {
			VECTOR wall = w2 - w1;
			VECTOR n; // 法線
			n.x = -wall.y;
			n.y = wall.x;
			n.z = 0.0;
			n = VNorm(n) * -1.0f;
			float push = VDot(n, velocity);// 壁を押す力の大きさは、
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
