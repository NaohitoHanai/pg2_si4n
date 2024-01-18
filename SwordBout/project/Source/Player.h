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

//	int hAnimRun; // ����A�j���[�V����
//	int hAnimStop; // �ҋ@�A�j���[�V����
	// �R�i�U����ǉ��i�A�j���[�V�������R�����܂��j
	enum ANIM_ID {
		A_STOP = 0,
		A_RUN,
		A_ATT1,
		A_ATT2,
		A_ATT3,
		MAX
	};
	int hAnimation[MAX];

	int attacking; // �U�����Ă��>0�A�U�����ĂȂ��Ƃ���0

	void AttackCheck();
	bool lastAttackKey; // �O��̍U���{�^���̏��

	bool CheckJumpKey();
};