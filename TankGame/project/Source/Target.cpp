#include "Target.h"

Target::Target()
{
	hModel = MV1LoadModel("data/target_001.mv1");
}

Target::Target(VECTOR pos)
{
	hModel = MV1LoadModel("data/target_001.mv1");
	position = pos;
}

Target::~Target()
{
}

void Target::Update()
{
}

void Target::Draw()
{
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
