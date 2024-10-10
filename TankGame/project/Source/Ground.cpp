#include "Ground.h"

Ground::Ground()
{
	hModel = MV1LoadModel("data/Stage00.mv1");
}

Ground::~Ground()
{
}

void Ground::Draw()
{
	MV1DrawModel(hModel);
}

float Ground::GetHeight(VECTOR pos)
{
	MV1_COLL_RESULT_POLY hit = MV1CollCheck_Line(hModel, 0, pos + VGet(0, 1000, 0), pos + VGet(0, -1000, 0));
	if (hit.HitFlag) {
		return hit.HitPosition.y;
	}
	return -10000.0f;
}
