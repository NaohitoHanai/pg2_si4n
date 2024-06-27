#include "Stage.h"
#include "StageObj.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

bool Stage::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
{
	bool ret = false;
	float dist = VSquareSize(p2 - p1);
	// �n�ʂ̃��f���ƁAStageObj�̗����œ��Ă�悤�ɂ���
	std::list<StageObj*> objs = ObjectManager::FindGameObjects<StageObj>();

	MV1_COLL_RESULT_POLY res =
		MV1CollCheck_Line(hModel, -1, p1, p2);
	if (res.HitFlag) // �������Ă���
	{
		// ���܂Ō��������̂�����O�ɂ��邩�H
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition; // �����������W��������
		}
		dist = VSquareSize(res.HitPosition - p1);
		ret = true;
	}

	for (StageObj* obj : objs) {
		MV1RefreshCollInfo(obj->CModel(), -1);
		MV1_COLL_RESULT_POLY res =
			MV1CollCheck_Line(obj->CModel(), -1, p1, p2);
		if (res.HitFlag) // �������Ă���
		{
			if (VSquareSize(res.HitPosition - p1) < dist) {
				if (hitPos != nullptr)
				{
					*hitPos = res.HitPosition; // �����������W��������
				}
				dist = VSquareSize(res.HitPosition - p1);
				ret = true;
			}
		}
	}
	return ret;
}
