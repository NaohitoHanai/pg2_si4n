#pragma once
#include "../Library/GameObject.h"
#include "animation.h"
#include <vector>

class Locus;

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
	void SetPosition(VECTOR pos) {
		position = pos;
	}

	bool Attacking() {
		return attacking>0;
	}
	VECTOR CameraPosition() {
		return cameraPosition;
	}

private:
	VECTOR cameraPosition;

	enum ANIM_ID {
		A_STOP = 0,
		A_RUN,
		A_ATT1,
		A_ATT2,
		A_ATT3,
		MAX
	};
	void setAnimation(ANIM_ID id, bool loop = true);
	void playAnimation();
	int animID;
	int hModel;

	int hWeapon;
	MATRIX mWeapon;

	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // ジャンプベクトル
	bool landing;

	Animation* animation;

//	int hAnimRun; // 走りアニメーション
//	int hAnimStop; // 待機アニメーション
	// ３段攻撃を追加（アニメーションが３つ増えます）
	struct TimeInfo {
		float time;
		bool used;
		std::string command;
		std::string filename;
	};
	struct AnimInfo{
		int hAnim;
		std::vector<TimeInfo> timeline;
		// アニメーションのタイムライン
	};
	AnimInfo info[MAX];
	bool canAttack; // 攻撃可能
	bool canCancel; // キャンセル可能

	int attacking; // 攻撃してれば>0、攻撃してないときは0

	void AttackCheck();
	bool lastAttackKey; // 前回の攻撃ボタンの状態

	bool CheckJumpKey();
	void reachToEnemy();

	Locus* locus;
};