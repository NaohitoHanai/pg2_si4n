#include "Player.h"
#include "Stage.h"
#include "../Library/Time.h"
#include "../ImGui/imgui.h"
#include "Dragon.h"
#include "Camera.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	hWeapon = MV1LoadModel("data/Character/Player/Sabel.mv1");

	std::string folder = "data/Character/Player/";
	std::string filename[] = {
		"Anim_Neutral",
		"Anim_Run",
		"Anim_Attack1",
		"Anim_Attack2",
		"Anim_Attack3",
	};
	for (int a = 0; a < MAX; a++) {
		hAnimation[a] = MV1LoadModel((folder + filename[a]+".mv1").c_str());
	}
	animation = new Animation();
	animation->SetModel(hModel); // アニメーションを付けるモデル
	animation->Play(hAnimation[A_STOP], true);

	position = VGet(0, 0, -500);
	rotation = VGet(0, 0, 0);
	lookTarget = VGet(0, 100, 0);
	lockOn = true;

	//仮に、ここに書いておく
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -500), VGet(0, 0, 0));

	attacking = 0;
}

Player::~Player()
{
}

void Player::Start()
{
}

void Player::Update()
{
	animation->Update();

	if (attacking == 0) {
		// WASDのキーから、入力方向のベクトルを作る
		VECTOR input = VGet(0, 0, 0);
		if (CheckHitKey(KEY_INPUT_W)) {
			input.z += 1.0f;
		}
		if (CheckHitKey(KEY_INPUT_S)) {
			input.z += -1.0f;
		}
		if (CheckHitKey(KEY_INPUT_D)) {
			input.x += 1.0f;
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			input.x += -1.0f;
		}
		float inputRot = atan2(input.x, input.z);
		if (input.x!=0 || input.z!=0) {
			Camera* cam = ObjectManager::FindGameObject<Camera>();
			VECTOR dir = cam->Direction();
			VECTOR moveVec = dir * 5.0f * MGetRotY(inputRot);
			position += moveVec;
			if (lockOn == false) {
				lookTarget += moveVec;
			}
			float rotateTarget = atan2(moveVec.x, moveVec.z);
			//rotation.yをrotateTargetに近づける
			//rotation.y = atan2(moveVec.x, moveVec.z);
			// 角度で補間する場合、
			// ①角度差を求める
			// ②その値をーπ～πの中に収める
			// ③角度差が一定角度(π/4）以内であれば、rotation.y=rotateTarget
			// ④値が＋であれば右回転、値が－であれば左回転でπ/4動かす
			animation->Play(hAnimation[A_RUN], true);
		}
		else {
			animation->Play(hAnimation[A_STOP], true);
		}
	}
	else {
		if (animation->IsEnd())
			attacking = 0;
	}
	AttackCheck();

	// 地面に立たせる
	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	if (pStage != nullptr)
	{
		VECTOR hit;
		if (pStage->CollLine( position+VGet(0,500,0), position+VGet(0,-500,0), &hit))
		{
			position = hit;
		}
	}
//	VECTOR cameraPos = VGet(0, 300, -500) * MGetRotY(rotation.y) + position;
//	VECTOR cameraPos = 
//		VGet(0, 300, -500) * MGetRotY(rotation.y) * MGetTranslate(position);
//	SetCameraPositionAndTarget_UpVecY( cameraPos, position );

//変数を見たいので
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &rotation.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::End();

	if (CheckHitKey(KEY_INPUT_F))
		Instantiate<Dragon>();
}

void Player::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);

	int wp = MV1SearchFrame(hModel, "wp");
	mWeapon = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hWeapon, mWeapon);
	MV1DrawModel(hWeapon);

	VECTOR p1 = VGet(0,0,0) * mWeapon;
	VECTOR p2 = VGet(0, -200, 0) * mWeapon;
	DrawLine3D(p1, p2, GetColor(255, 0, 0));
}

void Player::AttackCheck()
{
	// ここで攻撃入力判定して、攻撃モーションを再生する
	if (CheckHitKey(KEY_INPUT_M)) {
		if (!lastAttackKey) {  //押した瞬間
			//１段攻撃攻撃中で、animationのフレームが8を超えたら２段目にする
			if (attacking == 1 && animation->GetCurrentFrame() >= 8.5f) {
				animation->Play(hAnimation[A_ATT2], false);
				attacking = 2;
			}
			if (attacking == 2 && animation->GetCurrentFrame() >= 8.5f) {
				animation->Play(hAnimation[A_ATT3], false);
				attacking = 3;
			}
			if (attacking == 0) {
				animation->Play(hAnimation[A_ATT1], false);
				attacking = 1;
			}
		}
		lastAttackKey = true;
	}
	else { 
		lastAttackKey = false;
	}
	// 攻撃中の踏み込み
	if (attacking>0 && animation->GetCurrentFrame()<2.0f) {
		reachToEnemy();
	}
}

void Player::reachToEnemy()
{
}
