#pragma once
#include "../Library/GameObject.h"
#include "animation.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Start() override;
	void Update() override;
	void Draw() override;
	VECTOR Position() {
		return position;
	}
	bool Attacking() {
		return attacking>0;
	}

	VECTOR LookTarget() {
		return lookTarget;
	}

private:
	int hModel;

	int hWeapon;
	MATRIX mWeapon;

	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // ジャンプベクトル

	VECTOR lookTarget; // 注視点（ロックオンの場所）

	bool landing;

	Animation* animation;

//	int hAnimRun; // 走りアニメーション
//	int hAnimStop; // 待機アニメーション
	// ３段攻撃を追加（アニメーションが３つ増えます）
	enum ANIM_ID {
		A_STOP = 0,
		A_RUN,
		A_ATT1,
		A_ATT2,
		A_ATT3,
		MAX
	};
	int hAnimation[MAX];

	int attacking; // 攻撃してれば>0、攻撃してないときは0

	void AttackCheck();
	bool lastAttackKey; // 前回の攻撃ボタンの状態

	bool CheckJumpKey();
	void reachToEnemy();

	bool lockOn;
};