#include "Stage.h"
#include "Camera.h"

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

bool Stage::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos) const
{
	MV1_COLL_RESULT_POLY res =
		MV1CollCheck_Line(hModel, -1, p1, p2);
	if (res.HitFlag) // 当たっている
	{
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition; // 当たった座標がここに
		}
		return true;
	}
	return false;
}
