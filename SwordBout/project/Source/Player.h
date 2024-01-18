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
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // ジャンプベクトル
	bool landing;

	Animation* animation;

	int hAnimRun; // 走りアニメーション
	int hAnimStop; // 待機アニメーション
	// ３段攻撃を追加（アニメーションが３つ増えます）
//	int hAnimation[5];

	bool CheckJumpKey();
};