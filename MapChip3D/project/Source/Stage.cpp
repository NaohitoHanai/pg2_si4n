#include "Stage.h"
#include "Player.h"

const int map[4][6] = {
	{1,1,1,1,1,1,},
	{1,0,0,1,0,1,},
	{1,0,9,0,0,1,},
	{1,1,1,1,1,1,},
};

Stage::Stage()
{
	hWall = MV1LoadModel("data/wallEarth01.mv1");
	SetCameraPositionAndTarget_UpVecY(
		VGet(100, 1000, -400), VGet(0, 0, 0));
	for (int z = 0; z < 4; z++) {
		for (int x = 0; x < 6; x++) {
			if (map[z][x] == 9) {
				new Player(VGet(x*100, 0, -z*100));
			}
		}
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int z = 0; z < 4; z++) {
		for (int x = 0; x < 6; x++) {
			if (map[z][x] == 1) {
				VECTOR pos = VGet(x*100, 0, -z*100);
				MV1SetPosition(hWall, pos);
				MV1DrawModel(hWall);
			}
		}
	}
}
