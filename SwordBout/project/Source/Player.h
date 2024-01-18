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
	VECTOR jumpVelocity; // �W�����v�x�N�g��
	bool landing;

	Animation* animation;

	int hAnimRun; // ����A�j���[�V����
	int hAnimStop; // �ҋ@�A�j���[�V����
	// �R�i�U����ǉ��i�A�j���[�V�������R�����܂��j
//	int hAnimation[5];

	bool CheckJumpKey();
};