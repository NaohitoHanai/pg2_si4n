#include "Tank.h"
#include "../ImGui/imgui.h"
#include "Ground.h"
#include "Bullet.h"

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

	Ground* g = FindGameObject<Ground>();
	float y = g->GetHeight(position);
	if (y >= -9000.0f) {
		position.y = y;
	}
	float right = g->GetHeight(position + VGet(248, 0, 0) * MGetRotY(rotation.y));
	float left = g->GetHeight(position + VGet(-248, 0, 0) * MGetRotY(rotation.y));
	if (right >= -9000.f && left >= -9000.0f) {
		float b = 248 - (-248);
		float c = right - left;
		rotation.z = atan2(c, b);
	}
	float front = g->GetHeight(position + VGet(0, 0, -419) * MGetRotY(rotation.y));
	float back = g->GetHeight(position + VGet(0, 0, 464) * MGetRotY(rotation.y));
	if (front >= -9000.f && back >= -9000.0f) {
		float b = 464 - (-419);
		float c = front - back;
		rotation.x = atan2(c, b);
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

	SetCameraPositionAndTarget_UpVecY(
		VGet(0, 500, 900)*matrix,
		VGet(0, 100, 0)*matrix);
}

void TankTower::Draw()
{
	MATRIX ms = MGetScale(VGet(1.0f, 1.0f, 1.0f));
	MATRIX mr = MGetRotZ(rotation.z) *
		MGetRotX(rotation.x) * MGetRotY(rotation.y);
	MATRIX m = MGetTranslate(position);
	matrix = ms * mr * m;
	Tank* parent = FindGameObject<Tank>();
	matrix *= parent->Matrix();
	// matrixÇ…êeÅiTankÅjÇÃMatrixÇä|ÇØÇÈ
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
	if (CheckHitKey(KEY_INPUT_UP)) {
		rotation.x += DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x -= DegToRad(3.0f);
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {
		VECTOR pos = VGet(0,0,-400)*matrix; // Ç«Ç±Ç©ÇÁ
		VECTOR vel = VNorm(VGet(0, 0, -400)) * 100.0f;
		vel = VTransformSR(vel, matrix);
		new Bullet(pos, vel);
	}
}

void TankGun::Draw()
{
	MATRIX ms = MGetScale(VGet(1.0f, 1.0f, 1.0f));
	MATRIX mr = MGetRotZ(rotation.z) *
		MGetRotX(rotation.x) * MGetRotY(rotation.y);
	MATRIX m = MGetTranslate(position);
	matrix = ms * mr * m;
	TankTower* parent = FindGameObject<TankTower>();
	matrix *= parent->Matrix();
	// matrixÇ…êeÅiTankÅjÇÃMatrixÇä|ÇØÇÈ
	MV1SetMatrix(hModel, matrix);
	MV1DrawModel(hModel);

	// íeÇÃó\ë™ê¸Çï\é¶

}

void TankGun::PredictionLine(VECTOR pos, VECTOR vel)
{
}
