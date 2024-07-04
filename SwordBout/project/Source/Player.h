#pragma once
#include "../Library/GameObject.h"
#include "animation.h"
#include <vector>

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
	VECTOR jumpVelocity; // �W�����v�x�N�g��
	bool landing;

	Animation* animation;

//	int hAnimRun; // ����A�j���[�V����
//	int hAnimStop; // �ҋ@�A�j���[�V����
	// �R�i�U����ǉ��i�A�j���[�V�������R�����܂��j
	struct TimeInfo {
		float time;
		bool used;
		std::string command;
		std::string filename;
	};
	struct AnimInfo{
		int hAnim;
		std::vector<TimeInfo> timeline;
		// �A�j���[�V�����̃^�C�����C��
	};
	AnimInfo info[MAX];
	bool canAttack; // �U���\
	bool canCancel; // �L�����Z���\

	int attacking; // �U�����Ă��>0�A�U�����ĂȂ��Ƃ���0

	void AttackCheck();
	bool lastAttackKey; // �O��̍U���{�^���̏��

	bool CheckJumpKey();
	void reachToEnemy();
};