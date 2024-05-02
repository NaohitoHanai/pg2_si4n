#pragma once
//
// Goblin.h
//                   N.Hanai
//
#include "../Library/GameObject.h"
#include "GoblinAI.h"

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
	int hModel;
	VECTOR position;
	VECTOR rotation;
	GoblinAI* ai;
};