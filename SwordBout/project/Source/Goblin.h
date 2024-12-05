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
	void SetPosition(VECTOR pos) {
		position = pos;
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

	/// <summary>
	/// �_���[�W�����炤
	/// </summary>
	/// <param name="damageVal">�_���[�W��</param>
	/// <param name="dir">�m�b�N�o�b�N����x�N�g��</param>
	void AddDamage(int damageVal, VECTOR dir);
private:
	enum ANIM_ID {
		WAIT = 0,
		DAMAGE,
		BLOW_IN,
		BLOW_LOOP,
		BLOW_OUT,
		MAX
	};
	ANIM_ID animID;
	enum State {
		sWAIT = 0,
		sDAMAGE,
		sBLOW,
	};
	State state;
	int hModel;
	Animation* animation;
	int hAnim[MAX];
	VECTOR position;
	VECTOR rotation;

	float hp;
	bool damaged;
public:
	enum Message {
		ADD_DAMAGE = 1,
	};
private:
	void addDamage();

	int voiceTime;
	VECTOR lastLine1; // �O��̈ʒu
	VECTOR lastLine2;
};