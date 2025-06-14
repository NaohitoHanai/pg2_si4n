#include "BallManager.h"
#include "Ball.h"
#include "Pocket.h"

namespace {
	static const float CHARGE_MAX_TIME = 0.5f; // チャージMAXまでの時間
	static const float CHARGE_MAX_POWER = 4.0f; // チャージ最大時の威力
	static const RECT GAUGE = { 100, 400, 120, 600 }; // ゲージの表示場所（左、上、右、下）
};

BallManager::BallManager()
{
	Ball* my = Instantiate<Ball>();
	my->number = 16; // MY_NUMBERと定義しときたい
	my->position = VGet(200, 100, 0);
	balls.push_back(my);

	for (int i = 1; i <= 9; i++) {
		Ball* target = Instantiate <Ball>();
		target->number = i;
		target->position = VGet(100 * i, 180, 0);
		balls.push_back(target);
	}

	shotDir = VGet(1, 0, 0); // 発射する向き（ベクトル）
}

BallManager::~BallManager()
{
}

void BallManager::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		//shotDirを右に少し旋回する
		shotDir *= MGetRotZ(DegToRad(3.0f));
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		//shotDirを左に少し旋回する
		shotDir *= MGetRotZ(DegToRad(-3.0f));
	}
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		balls[0]->velocity += shotDir * 2.0f;
	}
	for (int b1 = 0; b1 < balls.size(); b1++) {
		balls[b1]->addPower = VGet(0, 0, 0); // addPowerをクリア
	}
	for (int b1 = 0; b1 < balls.size(); b1++) {
		for (int b2 = b1+1; b2 < balls.size(); b2++) {
			VECTOR pDiff = balls[b2]->position - balls[b1]->position;
			if (VSize(pDiff) < 64) {
				// 渡す速度の向き
				VECTOR dir = VNorm(pDiff); // 力を与える向き
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

	// 各ボールがポケットに入ったか調べる
	Pocket* pocket = FindGameObject<Pocket>();
	for (auto itr = balls.begin(); itr != balls.end(); itr++) {
		if (pocket->BallIn((*itr)->position, 32)) { // ポケットに入ったら
			(*itr)->DestroyMe(); // ball自身を削除
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
