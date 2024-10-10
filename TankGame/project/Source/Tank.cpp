#include "Tank.h"
#include "../ImGui/imgui.h"

Tank::Tank()
{
	new TankTower();

	hModel = MV1LoadModel("data/tank_001.mv1");
	position = VGet(0, 0, 0);
	rotation = VGet(0, DX_PI_F, 0);

	SetCameraPositionAndTarget_UpVecY(
		VGet(0, 300, -500),
		VGet(0, 0, 0));
}

Tank::~Tank()
{
}

void Tank::Update()
{
	if (CheckHitKey(KEY_INPUT_W)) {
		VECTOR forward = VGet(0, 0, -1) * MGetRotY(rotation.y);
		position += forward * 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		VECTOR forward = VGet(0, 0, -1) * MGetRotY(rotation.y);
		position -= forward * 10.0f;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		rotation.y += DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		rotation.y -= DegToRad(3.0f);
	}
}

void Tank::Draw()
{
	MATRIX ms = MGetScale(VGet(0.5f, 0.5f, 0.5f));
	MATRIX mr = MGetRotZ(rotation.z) * 
					MGetRotX(rotation.x) * MGetRotY(rotation.y);
	MATRIX m = MGetTranslate(position);
	matrix = ms * mr * m;
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}

TankTower::TankTower()
{
	new TankGun();

	hModel = MV1LoadModel("data/tank_tower_001.mv1");
	position = VGet(0, 200.0f, 0);
	rotation = VGet(0, 0, 0);
}

TankTower::~TankTower()
{
}

void TankTower::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rotation.y += DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y -= DegToRad(3.0f);
	}
}

// 問題
// 親子関係にある物体を描画するとき
// 子は、自分の行列を作った後、何を掛けて、
// 描画するか？

void TankTower::Draw()
{
	MATRIX ms = MGetScale(VGet(1.0f, 1.0f, 1.0f));
	MATRIX mr = MGetRotZ(rotation.z) *
		MGetRotX(rotation.x) * MGetRotY(rotation.y);
	MATRIX m = MGetTranslate(position);
	matrix = ms * mr * m;
	Tank* parent = FindGameObject<Tank>();
	matrix *= parent->Matrix();
	// matrixに親（Tank）のMatrixを掛ける
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}

TankGun::TankGun()
{
	hModel = MV1LoadModel("data/tank_gun_001.mv1");
	position = VGet(0, 53.5f, -146.7f);
	rotation = VGet(0, 0, 0);
}

TankGun::~TankGun()
{
}

void TankGun::Update()
{
}

void TankGun::Draw()
{
	MATRIX ms = MGetScale(VGet(1.0f, 1.0f, 1.0f));
	MATRIX mr = MGetRotZ(rotation.z) *
		MGetRotX(rotation.x) * MGetRotY(rotation.y);
	MATRIX m = MGetTranslate(position);
	MATRIX matrix = ms * mr * m;
	TankTower* parent = FindGameObject<TankTower>();
	matrix *= parent->Matrix();
	// matrixに親（Tank）のMatrixを掛ける
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);
}
