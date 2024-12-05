#include "Camera.h"
#include "Player.h"

Camera::Camera()
{
	SetCameraPositionAndTarget_UpVecY(
		VGet(0, 1000, -400), VGet(0, 0, 0));
}

Camera::~Camera()
{
}

void Camera::Update()
{
	Player* pl = FindGameObject<Player>();
	if (pl == nullptr)
		return;
	VECTOR pPos = pl->Position();
#if 0 // ‰ß‹Ž‚ð•Û‘¶‚·‚é•û–@
	if (lastPos.size() < 20) {
		lastPos.push_back(pPos);
	}
	else {
		for (int i = 0; i < 20 - 1; i++) {
			lastPos[i] = lastPos[i + 1];
		}
		lastPos[9] = pPos;
	}
	position = lastPos[0] + VGet(0, 1000, -400);
	lookAt = lastPos[0];
#endif
#if 1 // ‰~‚Ì”ÍˆÍ“à‚È‚ç‚Î“®‚©‚³‚È‚¢•û–@

#endif
}

void Camera::Draw()
{
	SetCameraPositionAndTarget_UpVecY(position, lookAt);
}
