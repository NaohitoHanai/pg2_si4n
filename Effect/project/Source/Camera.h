#pragma once
#include "../Library/GameObject.h"

class Camera : public GameObject {
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
	VECTOR Direction() {
		return direction;
	}
private:
	VECTOR position; // �J�������W
	VECTOR rotation; // �J��������p�̉�]
	VECTOR target; // �����_
	VECTOR direction; // �J�����̌����Ă�������̒P�ʃx�N�g��
};