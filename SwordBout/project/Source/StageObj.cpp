#include "StageObj.h"
#include <assert.h>

StageObj::StageObj()
{
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	scale = VGet(1, 1, 1);
	hModel = -1;
}

StageObj::~StageObj()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
	}
}

void StageObj::Draw()
{
	if (hModel > 0) {
		MV1SetPosition(hModel, position);
		MV1SetRotationXYZ(hModel, rotation);
		MV1SetScale(hModel, scale);
		MV1DrawModel(hModel);
	}
	if (hCModel > 0) {
		MV1SetPosition(hCModel, position);
		MV1SetRotationXYZ(hCModel, rotation);
		MV1SetScale(hCModel, scale);
//		MV1DrawModel(hCModel);
	}
}

void StageObj::LoadModel(int kind)
{
	assert(kind >= 0 && kind <= 999); // Debug‚ÌŽž‚¾‚¯—LŒø
	if (kind < 0 || kind > 999)
		return;
	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	char str[40];
	sprintf_s<40>(str, "data/Stage/Stage_Obj%03d.mv1", kind);
	hModel = MV1LoadModel(str);
	assert(hModel > 0);

	sprintf_s<40>(str, "data/Stage/Stage_Obj%03d_c.mv1", kind);
	hCModel = MV1LoadModel(str);
}

void StageObj::SetPosition(float x, float y, float z)
{
	position = VGet(x, y, z);
}

void StageObj::SetRotation(float x, float y, float z)
{
	rotation = VGet(x, y, z);
}

void StageObj::SetScale(float x, float y, float z)
{
	scale = VGet(x, y, z);
}
