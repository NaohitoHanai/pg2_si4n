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
