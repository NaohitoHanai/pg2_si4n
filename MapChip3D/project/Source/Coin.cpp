#include "Coin.h"
#include "Player.h"
#include "Score.h"

Coin::Coin()
{
}

Coin::Coin(const VECTOR& pos)
{
	hModel = MV1LoadModel("data/SpinningStar.mv1");
	position = pos;
	got = false;
	height = 0;
	rotation = 0.0f;
}

Coin::~Coin()
{
	if (hModel > 0) {
		MV1DeleteModel(hModel);
	}
}

void Coin::Update()
{
	if (got) { // 取得演出
		const float maxTime = 0.8f; // 最大時間
		//		height = sin((gotTimer/maxTime)*DegToRad(100.0f)) * 400.0f + 100.0f;
				//                              sin曲線のどこまで   高さ     最初の位置
		float x = (gotTimer / maxTime) * 1.5f;
		height = (-(x - 1) * (x - 1) + 1) * 400 + 100;
		gotTimer += Time::DeltaTime();
		rotation += DegToRad(30.0f);
		if (gotTimer > maxTime) {
			DestroyMe();
		}
		return;
	}
	Player* pl = FindGameObject<Player>();
	if (pl == nullptr) {
		return;
	}
	VECTOR pPos = pl->Position();
	rotation += DegToRad(1.0f);

	if (VSquareSize(pPos - position) < 40 * 40) {
		Score* sc = FindGameObject<Score>();
		sc->Add(100);
		got = true;
		gotTimer = 0.0f;
		velocity = -100.0f;
		height = 100.0f;
	}
}

void Coin::Draw()
{
	MV1SetScale(hModel, VGet(0.1f, 0.1f, 0.1f));
	MV1SetRotationXYZ(hModel, VGet(DX_PI_F/2.0f, rotation, 0));
	MV1SetPosition(hModel, position + VGet(0, height,0));
	MV1DrawModel(hModel);
}
