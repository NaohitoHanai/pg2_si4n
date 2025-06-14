#pragma once
#include "../Library/gameObject.h"

class Ball : public GameObject {
public:
	Ball();
	~Ball();
	void Update() override;
	void Draw() override;
//private: 面倒なので、とりあえず変数をいじれるようにする
	int hImage;
	int number; // ボールの番号
	VECTOR position; // ボールの中心座標
	VECTOR velocity; // 移動ベクトル
	VECTOR addPower; // 相手からもらった力
};