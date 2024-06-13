#include "SkyDoom.h"
#include "Camera.h"

SkyDoom::SkyDoom()
{
	hModel = MV1LoadModel("data/Stage/Stage00_sky.mv1");
	position = VGet(0, 0, 0);
}

SkyDoom::~SkyDoom()
{
}

void SkyDoom::Update()
{
	Camera* cam = ObjectManager::FindGameObject<Camera>();
	position = cam->Position();
}

void SkyDoom::Draw()
{
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
