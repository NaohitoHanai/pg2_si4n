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
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->Position();

	if (VSquareSize(pPos - position) < 40 * 40) {
		Score* sc = FindGameObject<Score>();
		sc->Add(100);
		DestroyMe();
	}
}

void Coin::Draw()
{
//	DrawSphere3D(position + VGet(0, 50, 0), 30, 20,
//		GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
	MV1SetScale(hModel, VGet(0.1f, 0.1f, 0.1f));
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
