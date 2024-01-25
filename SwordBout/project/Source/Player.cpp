#include "Player.h"
#include "Stage.h"
#include "Goblin.h"
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
	animation->SetModel(hModel); // ÉAÉjÉÅÅ[ÉVÉáÉìÇïtÇØÇÈÉÇÉfÉã
	animation->Play(hAnimation[A_STOP], true);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	//âºÇ…ÅAÇ±Ç±Ç…èëÇ¢ÇƒÇ®Ç≠
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

			MATRIX rotY = MGetRotY(rotation.y); // âÒì]çsóÒÇçÏÇÈ
			VECTOR move = VGet(0, 0, 2);  // âÒì]ÇµÇƒÇ»Ç¢éûÇÃà⁄ìÆÉxÉNÉgÉã
			VECTOR forward = move * rotY; // âÒì]çsóÒÇä|ÇØÇÈÇ∆forward
			position += forward;
			// UnityÇ¡Ç€Ç≠èëÇ≠Ç»ÇÁ
			//MATRIX rotY = MGetRotY(rotation.y); // âÒì]çsóÒÇçÏÇÈ
			//VECTOR move = VGet(0, 0, 1);  // âÒì]ÇµÇƒÇ»Ç¢éûÇÃí∑Ç≥ÇPÇÃÉxÉNÉgÉã
			//VECTOR forward = move * rotY; // âÒì]çsóÒÇä|ÇØÇÈÇ∆forward
			//position += forward * 2.0f; // Ç±Ç±Ç≈ë¨ìxÇä|ÇØÇÈ
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

	// ínñ Ç…óßÇΩÇπÇÈ
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

	// çUåÇîªíË
	if (attacking > 0) {
		VECTOR p1 = VGet(0, 0, 0) * mWeapon;
		VECTOR p2 = VGet(0, -200, 0) * mWeapon;
		Goblin* pGoblin = ObjectManager::FindGameObject<Goblin>();
		pGoblin->PlayerAttack(position, p1, p2);
	}

//ïœêîÇå©ÇΩÇ¢ÇÃÇ≈
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
	// Ç±Ç±Ç≈çUåÇì¸óÕîªíËÇµÇƒÅAçUåÇÉÇÅ[ÉVÉáÉìÇçƒê∂Ç∑ÇÈ
	if (CheckHitKey(KEY_INPUT_M)) {
		if (!lastAttackKey) {  //âüÇµÇΩèuä‘
			//ÇPíiçUåÇçUåÇíÜÇ≈ÅAanimationÇÃÉtÉåÅ[ÉÄÇ™8Çí¥Ç¶ÇΩÇÁÇQíiñ⁄Ç…Ç∑ÇÈ
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
				reachToEnemy();
			}
		}
		lastAttackKey = true;
	}
	else { 
		lastAttackKey = false;
	}
}

void Player::reachToEnemy()
{
	// éãñÏì‡Ç…ì¸Ç¡ÇΩÇ©ÅH
	Goblin* pGoblin = ObjectManager::FindGameObject<Goblin>();
	VECTOR dist = pGoblin->Position() - position;
	dist.y = 0;
	// éãñÏÇÕÅAãóó£ÇQÇTÇOà»ì‡ÅAÇRÇOìxà»ì‡
	if (VSize(dist) >= 250.0)
		return;
	// äpìxî≈
//	float toGoblin = atan2(dist.x, dist.z);
//	float diff = toGoblin - rotation.y;
//	while (diff >= DegToRad(180.0f))
//		diff -= DegToRad(360.0f);
//	while (diff < DegToRad(-180.0f))
//		diff += DegToRad(360.0f);
//	if (diff >= DegToRad(30.0f) || diff <= DegToRad(-30.0f))
//		return;
	// ì‡êœî≈
	dist = VNorm(dist); // ÉSÉuÉäÉìÇ÷ÇÃÉxÉNÉgÉãÇÃí∑Ç≥ÇP
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
	float ip = VDot(dist, forward); // ì‡êœÇãÅÇﬂÇÈÅBÇ¬Ç‹ÇËcos
	if (ip < DegToRad(30.0f))
		return;

	//Memo PlayerÇÃå¸Ç´ÇÕÅArotation.y
	// 30ìxÇÉâÉWÉAÉìÇ…Ç∑ÇÈÇ…ÇÕÅADegToRad(30.0f)
	// ì¸Ç¡ÇΩÇÃÇ≈ÅAÇªÇøÇÁÇ…ãﬂÇ√Ç≠
}
