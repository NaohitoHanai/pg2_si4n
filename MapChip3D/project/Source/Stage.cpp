#include "Stage.h"
#include "Player.h"
#include "Coin.h"
#include <vector>

using namespace std;

const vector<string> map = {
	"WWWWWWWWWW",
	"W  W  c  W",
	"W o  c WWW",
	"WWWWWWWW",
};

Stage::Stage()
{
	hWall = MV1LoadModel("data/wallEarth01.mv1");
	SetCameraPositionAndTarget_UpVecY(
		VGet(100, 1000, -400), VGet(0, 0, 0));
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 'o') {
				new Player(VGet(x*100, 0, -z*100));
			}
			if (map[z][x] == 'c') {
				new Coin(VGet(x * 100, 0, -z * 100));
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
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 'W') {
				VECTOR pos = VGet(x*100, 0, -z*100);
				MV1SetPosition(hWall, pos);
				MV1DrawModel(hWall);
			}
		}
	}
}

const VECTOR& Stage::CollisionSphere(const VECTOR& pos, SphereCollider* col)
{
	VECTOR ret = VGet(0, 0, 0);
	for (int z = 0; z < map.size(); z++) {
		for (int x = 0; x < map[z].size(); x++) {
			if (map[z][x] == 'W') {
				VECTOR vc = VGet(x * 100, 0, -z * 100);
				std::vector<VECTOR> vo;
				vo.push_back(VGet(-50, 0, -50));
				vo.push_back(VGet(-50, 0, 50));
				vo.push_back(VGet(-50, 100, 50));
				vo.push_back(VGet(-50, 100, -50));
				VECTOR normal = VGet(-1, 0, 0);
				for (int i = 0; i < 4; i++) {
					VECTOR v[4];
					for (int j = 0; j < vo.size(); j++) {
						v[j] = vc + vo[j];
					}
					ret += collisionSquare(pos, col, v, normal);
					normal *= MGetRotY(DX_PI_F / 2.0f);
					for (int j = 0; j < 4; j++) {
						vo[j] *= MGetRotY(DX_PI_F / 2.0f);
					}
				}
			}
		}
	}
	return ret;
}

const VECTOR& Stage::collisionSquare(const VECTOR& pos, SphereCollider* col, VECTOR v[4], VECTOR normal)
{
	VECTOR a = pos + col->offset - v[0];
	float dist = VDot(a, normal);
	if (dist < 0 || dist > col->radius) {
		return VGet(0,0,0);
	}
	VECTOR xp = pos + col->offset - normal * dist;
	// xp‚ªŽlŠpŒ`‚Ì“à‘¤‚©
	VECTOR op0 = VCross(xp - v[0], v[1] - v[0]);
	VECTOR op1 = VCross(xp - v[1], v[2] - v[1]);
	VECTOR op2 = VCross(xp - v[2], v[3] - v[2]);
	VECTOR op3 = VCross(xp - v[3], v[0] - v[3]);
	if (VDot(op0, op1) > 0 && VDot(op0, op2) > 0 && VDot(op0, op3) > 0) {
		// “–‚½‚Á‚½
		return normal * (col->radius - dist);
	}
	return VGet(0, 0, 0);
}
