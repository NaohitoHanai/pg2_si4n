#pragma once
#include "../Library/GameObject.h"

class Score : public GameObject {
public:
	Score();
	~Score();
	void Update() override;
	void Draw() override;
	void Add(int val);
private:
	int score; // ���ۂ̃X�R�A
	int viewScore; // �\���̃X�R�A
};