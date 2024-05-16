#include "Player.h"
#include "Stage.h"
#include "../Library/Time.h"
#include "../ImGui/imgui.h"

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
	animation->SetModel(hModel); // ƒAƒjƒ[ƒVƒ‡ƒ“‚ð•t‚¯‚éƒ‚ƒfƒ‹
	animation->Play(hAnimation[A_STOP], true);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	//‰¼‚ÉA‚±‚±‚É‘‚¢‚Ä‚¨‚­
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
		if (CheckHitKey(KEY_INPUT_W))
		{
			//position.z += cosf(rotation.y) * 2.0f;
			//position.x += sinf(rotation.y) * 2.0f;

			MATRIX rotY = MGetRotY(rotation.y); // ‰ñ“]s—ñ‚ðì‚é
			VECTOR move = VGet(0, 0, 2);  // ‰ñ“]‚µ‚Ä‚È‚¢Žž‚ÌˆÚ“®ƒxƒNƒgƒ‹
			VECTOR forward = move * rotY; // ‰ñ“]s—ñ‚ðŠ|‚¯‚é‚Æforward
			position += forward;
			// Unity‚Á‚Û‚­‘‚­‚È‚ç
			//MATRIX rotY = MGetRotY(rotation.y); // ‰ñ“]s—ñ‚ðì‚é
			//VECTOR move = VGet(0, 0, 1);  // ‰ñ“]‚µ‚Ä‚È‚¢Žž‚Ì’·‚³‚P‚ÌƒxƒNƒgƒ‹
			//VECTOR forward = move * rotY; // ‰ñ“]s—ñ‚ðŠ|‚¯‚é‚Æforward
			//position += forward * 2.0f; // ‚±‚±‚Å‘¬“x‚ðŠ|‚¯‚é
			animation->Play(hAnimation[A_RUN], true);
		}
		else {
			animation->Play(hAnimation[A_STOP], true);
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			rotation.y += 3.0f * DX_PI_F / 180.0f;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			rotation.y -= 3.0f * DX_PI_F / 180.0f;
		}
	}
	else {
		if (animation->IsEnd())
			attacking = 0;
	}
	AttackCheck();

	// ’n–Ê‚É—§‚½‚¹‚é
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
	VECTOR cameraPos = 
		VGet(0, 300, -500) * MGetRotY(rotation.y) * MGetTranslate(position);
	SetCameraPositionAndTarget_UpVecY( cameraPos, position );

//•Ï”‚ðŒ©‚½‚¢‚Ì‚Å
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &rotation.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::End();
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
	// ‚±‚±‚ÅUŒ‚“ü—Í”»’è‚µ‚ÄAUŒ‚ƒ‚[ƒVƒ‡ƒ“‚ðÄ¶‚·‚é
	if (CheckHitKey(KEY_INPUT_M)) {
		if (!lastAttackKey) {  //‰Ÿ‚µ‚½uŠÔ
			//‚P’iUŒ‚UŒ‚’†‚ÅAanimation‚ÌƒtƒŒ[ƒ€‚ª8‚ð’´‚¦‚½‚ç‚Q’i–Ú‚É‚·‚é
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
	// UŒ‚’†‚Ì“¥‚Ýž‚Ý
	if (attacking>0 && animation->GetCurrentFrame()<2.0f) {
		reachToEnemy();
	}
}

void Player::reachToEnemy()
{
}
