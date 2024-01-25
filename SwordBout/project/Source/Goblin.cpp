#include "Goblin.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	position = VGet(0, 100, 300);
	rotation = VGet(0, 0, 0);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
}

void Goblin::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

VECTOR lastLine1; // �O��̈ʒu
VECTOR lastLine2;

bool Goblin::PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2)
{
	// �S�{�̐��œ������Ă��邩���ׂ�
	bool hit = false;
	for (int i = 1; i <= 4; i++) {
		VECTOR p1 = (weaponLine1 - lastLine1) * (i / 4.0f) + lastLine1;
		VECTOR p2 = (weaponLine2 - lastLine2) * (i / 4.0f) + lastLine2;
		MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
		if (res.HitFlag) // �������Ă���
		{
			hit = true;
		}
	}
	// ���������̂Ńm�b�N�o�b�N
	if (hit) {
		VECTOR addVec = position - playerPos;
		addVec.y = 0;
		addVec = VNorm(addVec) * 50.0f;
		position += addVec;
	}
	// �S�{���̂��߂ɁA������ۑ�����
	lastLine1 = weaponLine1;
	lastLine2 = weaponLine2;
	return hit;
}
