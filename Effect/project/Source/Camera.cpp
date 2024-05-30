#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	rotation = VGet(0, 0, 0);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		rotation.y += DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT)) {
		rotation.y -= DegToRad(3.0f);
	}
	if (CheckHitKey(KEY_INPUT_UP)) {
		rotation.x += DegToRad(3.0f);
		if (rotation.x > DegToRad(60.0f))
			rotation.x = DegToRad(60.0f);
	}
	if (CheckHitKey(KEY_INPUT_DOWN)) {
		rotation.x -= DegToRad(3.0f);
		if (rotation.x < DegToRad(-60.0f))
			rotation.x = DegToRad(-60.0f);
	}
	Player* pl = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pl->Position();
	VECTOR pLook = pl->LookTarget();
	//ToDo: position��target�����߂�
	VECTOR v = pPos - pLook;
	v.y = 0;
	v = VNorm(v) * 330.0f;
	v.y = 300.0f - 100.0f;
	VECTOR center = pPos + VGet(0, 100, 0); // �v���C���[�L�����̐S��
	MATRIX mRot = MGetRotX(rotation.x) * MGetRotY(rotation.y);
	position = center + v * mRot; // �J�������W
	VECTOR lk = pLook - center;
	target = center + lk * mRot; // �����_
	direction = target - position;
	direction.y = 0;
	direction = VNorm(direction);
}

void Camera::Draw()
{
	SetCameraPositionAndTarget_UpVecY(position, target);
}