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
	if (res.HitFlag) // ìñÇΩÇ¡ÇƒÇ¢ÇÈ
	{
		if (hitPos != nullptr)
		{
			*hitPos = res.HitPosition; // ìñÇΩÇ¡ÇΩç¿ïWÇ™Ç±Ç±Ç…
		}
		return true;
	}
	return false;
}
