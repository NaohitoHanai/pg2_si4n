#pragma once
#include "../Library/gameObject.h"

class Ball : public GameObject {
public:
	Ball();
	~Ball();
	void Update() override;
	void Draw() override;
//private: �ʓ|�Ȃ̂ŁA�Ƃ肠�����ϐ����������悤�ɂ���
	int hImage;
	int number; // �{�[���̔ԍ�
	VECTOR position; // �{�[���̒��S���W
	VECTOR velocity; // �ړ��x�N�g��
	VECTOR addPower; // ���肩����������
};