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
	// 地面のモデルと、StageObjの両方で当てるようにする
	std::list<StageObj*> objs = ObjectManager::FindGameObjects<StageObj>();

	MV1_COLL_RESULT_POLY res =
		MV1CollCheck_Line(hModel, -1, p1, p2);
	if (res.HitFlag) // 当たっている
	{
		// 今まで見つけたものよりも手前にあるか？
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition; // 当たった座標がここに
		}
		dist = VSquareSize(res.HitPosition - p1);
		ret = true;
	}

	for (StageObj* obj : objs) {
		MV1RefreshCollInfo(obj->CModel(), -1);
		MV1_COLL_RESULT_POLY res =
			MV1CollCheck_Line(obj->CModel(), -1, p1, p2);
		if (res.HitFlag) // 当たっている
		{
			if (VSquareSize(res.HitPosition - p1) < dist) {
				if (hitPos != nullptr)
				{
					*hitPos = res.HitPosition; // 当たった座標がここに
				}
				dist = VSquareSize(res.HitPosition - p1);
				ret = true;
			}
		}
	}
	return ret;
}
