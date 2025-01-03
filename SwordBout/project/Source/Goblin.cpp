#include "Goblin.h"
#include "Stage.h"
#include "Player.h"
#include "../ImGui/imgui.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animation = new Animation();
	animation->SetModel(hModel);
	hAnim[WAIT] = MV1LoadModel("data/Character/Goblin/Anim_Neutral.mv1");
	hAnim[DAMAGE] = MV1LoadModel("data/Character/Goblin/Anim_Damage.mv1");
	hAnim[BLOW_IN] = MV1LoadModel("data/Character/Goblin/Anim_Blow_In.mv1");
	hAnim[BLOW_LOOP] = MV1LoadModel("data/Character/Goblin/Anim_Blow_Loop.mv1");
	hAnim[BLOW_OUT] = MV1LoadModel("data/Character/Goblin/Anim_Blow_Out.mv1");
	position = VGet(0, 100, 300);
	rotation = VGet(0, 0, 0);

	state = sWAIT;
	animation->Play(hAnim[WAIT]);

	voiceTime = 0;

	hp = 30; // ３回ダメージで死亡
	damaged = false;
}

Goblin::~Goblin()
{
}

void Goblin::Update()
{
	voiceTime--;
	if (voiceTime <= 0) {
		Player* pPlayer = ObjectManager::FindGameObject<Player>();
		VECTOR camPos = pPlayer->CameraPosition(); // カメラ座標
		float distance = VSize(camPos - position); // 距離
		int volume = (distance - 600) * (-255) / 1400;
		if (volume > 255)
			volume = 255;

		VECTOR camVec = pPlayer->Position() - camPos; // カメラの正面ベクトル
		camVec.y = 0;
		VECTOR camRight = VNorm(camVec) * MGetRotY(DX_PI / 2.0f);
		VECTOR myVec = VNorm(position - camPos);
		int pan = VDot(camRight, myVec) * 255.0f; // 計算する
		if (volume > 0) {
			int hSound = LoadSoundMem("data/sound/SE/Goblin/VO_dead_00.wav");
			PlaySoundMem(hSound, DX_PLAYTYPE_BACK);
			ChangeVolumeSoundMem(volume, hSound); // 0で無音、255で最大
			ChangePanSoundMem(pan, hSound); // -255で左、255で右
		}
		voiceTime = GetRand(120) + 120;
	}

	switch (message.PopMessage()) {
	case ADD_DAMAGE:
		addDamage();
		break;
	}
	animation->Update();
//	ai->Update();
	if (state == sDAMAGE) {
		if (animation->IsEnd()) {
			animation->Play(hAnim[WAIT]);
			state = sWAIT;
		}
	}
	else if (state == sBLOW) {

		if (animation->IsEnd()) {
			animation->Play(hAnim[BLOW_LOOP]);
		}
	}
//	Player* pPlayer = ObjectManager::FindGameObject<Player>();
//	if (pPlayer != nullptr) {
//		VECTOR target = pPlayer->Position() - position;
//		target.y = 0.0f;
//#if 0 // 内積バージョン
//		VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
//		float targetCos = VDot(VNorm(target), forward);
//		// 正面にいない場合、そちらの方を向く
//		static const float Limit = 5.0f; // 視野（°）
//		if (targetCos <= cos(DegToRad(Limit))) {
//			VECTOR right = VGet(1, 0, 0) * MGetRotY(rotation.y);
//			float ip = VDot(target, right);
//			if (ip >= 0) {
//				rotation.y += DegToRad(Limit);
//			}
//			else {
//				rotation.y -= DegToRad(Limit);
//			}
//		}
//#endif
//#if 1 // 角度バージョン
//		float targetAngle = atan2(target.x, target.z);
//		float diff = targetAngle - rotation.y; // 角度の差を取る
//		// diffを±PIの中に納める
//		while (diff > DX_PI_F) {
//			diff -= DX_PI_F * 2.0f;
//		}
//		while (diff < -DX_PI_F) {
//			diff += DX_PI_F * 2.0f;
//		}
//		if (diff>0)
//			rotation.y += DegToRad(3.0f);
//		if (diff<0)
//			rotation.y -= DegToRad(3.0f);
//#endif
//	}
//
//	VECTOR move = VGet(0, 0, 1) * MGetRotY(rotation.y) * 1.5f;
//	position += move;

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

bool Goblin::PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2)
{
	MV1SetupCollInfo(hModel, -1, 4, 4, 4, -1); 
	MV1RefreshCollInfo(hModel);
	bool hit = false;
	auto ret = MV1CollCheck_Triangle(
		hModel, -1,
		weaponLine1, weaponLine2, lastLine1);
	if (ret.HitNum > 0) {
		hit = true;
	}
	ret = MV1CollCheck_Triangle(
		hModel, -1,
		lastLine1, weaponLine2, lastLine2);
	if (ret.HitNum > 0) {
		hit = true;
	}
	//// ４本の線で当た
	//// っているか調べる
	//bool hit = false;
	//for (int i = 1; i <= 4; i++) {
	//	VECTOR p1 = (weaponLine1 - lastLine1) * (i / 4.0f) + lastLine1;
	//	VECTOR p2 = (weaponLine2 - lastLine2) * (i / 4.0f) + lastLine2;
	//	MV1_COLL_RESULT_POLY res = MV1CollCheck_Line(hModel, -1, p1, p2);
	//	if (res.HitFlag) // 当たっている
	//	{
	//		hit = true;
	//	}
	//}
	
	// ４本線のために、線情報を保存する
	lastLine1 = weaponLine1;
	lastLine2 = weaponLine2;
	if (hit && damaged) {
		return false;
	}
	if (hit) {
		damaged = true;
	}
	else {
		damaged = false;
	}
	return hit;
}

void Goblin::AddDamage(int damageVal, VECTOR dir)
{
	rotation.y = atan2(dir.x, dir.z);
	hp -= damageVal;
	if (hp <= 0) {
		state = sBLOW;
		animation->Play(hAnim[BLOW_IN], false);
	}
	else {
		state = sDAMAGE;
		animation->PlayForce(hAnim[DAMAGE], false);
		position += dir;
	}
}

void Goblin::addDamage()
{
	state = sDAMAGE;
	animation->Play(hAnim[DAMAGE], false);
}