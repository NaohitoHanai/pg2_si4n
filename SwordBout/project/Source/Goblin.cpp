#include "Goblin.h"
#include "Stage.h"
#include "Player.h"
#include "../ImGui/imgui.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	position = VGet(0, 100, 300);
	rotation = VGet(0, 0, 0);
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	if (pPlayer != nullptr) {
		VECTOR target = pPlayer->Position() - position;
		target.y = 0.0f;
#if 1 // 内積バージョン
		VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
		float targetCos = VDot(VNorm(target), forward);
		// 正面のベクトルと、targetの長さ１と内積を取る
		// 内積が、どうなったら？
		if (targetCos <= cos(DegToRad(3.0f))) {
			VECTOR right = VGet(1, 0, 0) * MGetRotY(rotation.y);
			// 内積( VDot()関数を使って求める )
			float ip = VDot(target, right);
			// >0→右回転
			if (ip >= 0) {
				rotation.y += DegToRad(3.0f);
			}
			else {
				rotation.y -= DegToRad(3.0f);
			}
		}
#endif
#if 0 // 角度バージョン
		float targetAngle = atan2(target.x, target.z);
		float diff = targetAngle - rotation.y; // 角度の差を取る
		// diffを±PIの中に納める
		while (diff > DX_PI_F) {
			diff -= DX_PI_F * 2.0f;
		}
		while (diff < -DX_PI_F) {
			diff += DX_PI_F * 2.0f;
		}
		if (diff>0)
			rotation.y += DegToRad(3.0f);
		if (diff<0)
			rotation.y -= DegToRad(3.0f);
#endif
	}

	VECTOR move = VGet(0, 0, 1) * MGetRotY(rotation.y) * 1.5f;
	position += move;

	// 地面に立たせる
	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr)
	{
		VECTOR hit;
		if (pStage->CollLine(position + VGet(0, 500, 0), position + VGet(0, -500, 0), &hit))
		{
			position = hit;
		}
	}
}

void Goblin::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

VECTOR lastLine1; // 前回の位置
VECTOR lastLine2;

bool Goblin::PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2)
{
	// ４本の線で当たっているか調べる
	bool hit = false;
	for (int i = 1; i <= 4; i++) {
		VECTOR p1 = (weaponLine1 - lastLine1) * (i / 4.0f) + lastLine1;
		VECTOR p2 = (weaponLine2 - lastLine2) * (i / 4.0f) + lastLine2;
		MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
		if (res.HitFlag) // 当たっている
		{
			hit = true;
		}
	}
	// 当たったのでノックバック
	if (hit) {
		VECTOR addVec = position - playerPos;
		addVec.y = 0;
		addVec = VNorm(addVec) * 50.0f;
		position += addVec;
	}
	// ４本線のために、線情報を保存する
	lastLine1 = weaponLine1;
	lastLine2 = weaponLine2;
	return hit;
}
