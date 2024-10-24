#pragma once
//Stage.h
#include "../Library/GameObject.h"
#include "SphereCollider.h"

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	const VECTOR& CollisionSphere(const VECTOR& pos, SphereCollider* col);
	//�ǂƓ��ĂāA�����Ԃ������Ɨʂ�Ԃ�
private:
	int hWall; // �ǂ̃��f��
};