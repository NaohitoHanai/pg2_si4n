#pragma once
//
// Goblin.h
//                   N.Hanai
//
#include "../Library/GameObject.h"
#include "GoblinAI.h"
#include "animation.h"

/// <summary>
/// �S�u�����L����
/// </summary>
class Goblin : public GameObject
{
public:
	Goblin();
	~Goblin();
	void Update() override;
	void Draw() override;
	void SetPosition(float x, float y, float z) {
		position = VGet(x, y, z);
	}

	/// <summary>
	/// �v���C���[����̍U�����󂯂�
	/// �����ƃ��f���Ƃ𓖂ĂāA����������A�v���C���[��
	/// ���Α��ɔ��
	/// </summary>
	/// <param name="playerPos">�v���C���[�̈ʒu</param>
	/// <param name="weaponLine1">�U�����P</param>
	/// <param name="weaponLine2">�U�����Q</param>
	/// <returns>����������true</returns>
	bool PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2);

	VECTOR Position() {
		return position;
	}
	void AddPosition(const VECTOR& pos) {
		position += pos;
	}
private:
	enum ANIM_ID {
		WAIT = 0,
		DAMAGE,
		MAX
	};
	ANIM_ID animID;
	enum State {
		sWAIT = 0,
		sDAMAGE,
	};
	State state;
	int hModel;
	Animation* animation;
	int hAnim[MAX];
	VECTOR position;
	VECTOR rotation;

public:
	enum Message {
		ADD_DAMAGE = 1,
	};
private:
	void addDamage();

	int voiceTime;
};