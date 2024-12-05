#include "Player.h"
#include "Stage.h"
#include "Goblin.h"
#include "../Library/Time.h"
#include "../ImGui/imgui.h"
#include "csvReader.h"

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
		info[a].hAnim = MV1LoadModel((folder + filename[a]+".mv1").c_str());
		// csv��ǂ��timeline�����
		CsvReader* csv = new CsvReader(folder + filename[a] + ".csv");
		for (int ln = 0; ln < csv->GetLines(); ln++) {
			TimeInfo ti;
			ti.time = csv->GetFloat(ln, 0);
			ti.command = csv->GetString(ln, 1);
			ti.filename = csv->GetString(ln, 2);
			info[a].timeline.push_back(ti);
		}
		delete csv;
	}
	animation = new Animation();
	animation->SetModel(hModel); // �A�j���[�V������t���郂�f��
	setAnimation(A_STOP, true);

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	//���ɁA�����ɏ����Ă���
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
	playAnimation();

	if (attacking == 0) {
		if (CheckHitKey(KEY_INPUT_W))
		{
			//position.z += cosf(rotation.y) * 2.0f;
			//position.x += sinf(rotation.y) * 2.0f;

			MATRIX rotY = MGetRotY(rotation.y); // ��]�s������
			VECTOR move = VGet(0, 0, 10);  // ��]���ĂȂ����̈ړ��x�N�g��
			VECTOR forward = move * rotY; // ��]�s����|�����forward
			position += forward;
			// Unity���ۂ������Ȃ�
			//MATRIX rotY = MGetRotY(rotation.y); // ��]�s������
			//VECTOR move = VGet(0, 0, 1);  // ��]���ĂȂ����̒����P�̃x�N�g��
			//VECTOR forward = move * rotY; // ��]�s����|�����forward
			//position += forward * 2.0f; // �����ő��x���|����
			setAnimation(A_RUN, true);
		}
		else {
			setAnimation(A_STOP, true);
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
		if (animation->GetCurrentFrame() < 5) {
			MATRIX rotY = MGetRotY(rotation.y); // ��]�s������
			VECTOR move = VGet(0, 0, 5);  // ��]���ĂȂ����̈ړ��x�N�g��
			VECTOR forward = move * rotY; // ��]�s����|�����forward
			position += forward;
		}
		if (animation->IsEnd())
			attacking = 0;
	}
	AttackCheck();

	// �n�ʂɗ�������
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
	cameraPosition = 
		VGet(0, 300, -500) * MGetRotY(rotation.y) * MGetTranslate(position);
	SetCameraPositionAndTarget_UpVecY( cameraPosition, position );

	// �U������
	if (attacking > 0) {
		if (canAttack) {
			VECTOR p1 = VGet(0, 0, 0) * mWeapon;
			VECTOR p2 = VGet(0, -200, 0) * mWeapon;
			std::list<Goblin*> pGoblins = ObjectManager::FindGameObjects<Goblin>();
			for (Goblin* pGoblin : pGoblins) {
				if (pGoblin->PlayerAttack(position, position, p2)) {
//					MessageQueue::Param p;
//					p.intVal = 10;
//					pGoblin->message.ReceiveMessage(
//						Goblin::ADD_DAMAGE, p);
					MATRIX rotY = MGetRotY(rotation.y); // ��]�s������
					VECTOR move = VGet(0, 0, 30);  // ��]���ĂȂ����̈ړ��x�N�g��
					VECTOR forward = move * rotY; // ��]�s����|�����forward
					pGoblin->AddDamage(10, forward);
				}
			}
		}
	}

//�ϐ����������̂�
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

void Player::setAnimation(ANIM_ID id, bool loop)
{
	animation->Play(info[id].hAnim, loop);
	animID = id;
	canAttack = false;
	canCancel = false;
}

void Player::playAnimation()
{
	float prevFrame = animation->GetCurrentFrame();
	animation->Update();
	float curFrame = animation->GetCurrentFrame();

	std::string folder = "data/sound/SE/";
	for (TimeInfo t : info[animID].timeline) {
		if (t.time > prevFrame && t.time <= curFrame) {
			if (t.command == "SE") {
				PlaySound(
					(folder + t.filename + "_00.wav").c_str(),
					DX_PLAYTYPE_BACK);
			}
			else if (t.command == "MatSE") {
				PlaySound((folder + t.filename + "_stone_00.wav")
					.c_str(), DX_PLAYTYPE_BACK);
			}
			else if (t.command == "AttackStart") {
				canAttack = true;
			}
			else if (t.command == "AttackEnd") {
				canAttack = false;
			}
			else if (t.command == "Cancel") {
				canCancel = true;
			}
		}
	}
}

void Player::AttackCheck()
{
	// �����ōU�����͔��肵�āA�U�����[�V�������Đ�����
	if (CheckHitKey(KEY_INPUT_M)) {
		if (!lastAttackKey) {  //�������u��
			//�P�i�U���U�����ŁAanimation�̃t���[����8�𒴂�����Q�i�ڂɂ���
			if (attacking == 1 && canCancel) {
				setAnimation(A_ATT2, false);
				attacking = 2;
			}
			if (attacking == 2 && canCancel) {
				setAnimation(A_ATT3, false);
				attacking = 3;
			}
			if (attacking == 0) {
				setAnimation(A_ATT1, false);
				attacking = 1;
			}
		}
		lastAttackKey = true;
	}
	else { 
		lastAttackKey = false;
	}
	// �U�����̓��ݍ���
	if (attacking>0 && animation->GetCurrentFrame()<2.0f) {
		reachToEnemy();
	}
}

void Player::reachToEnemy()
{
	// ������ɓ��������H
	Goblin* pGoblin = ObjectManager::FindGameObject<Goblin>();
	VECTOR dist = pGoblin->Position() - position;
	dist.y = 0;
	// ����́A�����Q�T�O�ȓ��A�R�O�x�ȓ�
	if (VSize(dist) >= 500.0)
		return;
	// �p�x��
//	float toGoblin = atan2(dist.x, dist.z);
//	float diff = toGoblin - rotation.y;
//	while (diff >= DegToRad(180.0f))
//		diff -= DegToRad(360.0f);
//	while (diff < DegToRad(-180.0f))
//		diff += DegToRad(360.0f);
//	if (diff >= DegToRad(30.0f) || diff <= DegToRad(-30.0f))
//		return;
	// ���ϔ�
	dist = VNorm(dist); // �S�u�����ւ̃x�N�g���̒����P
	VECTOR forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
	float ip = VDot(dist, forward); // ���ς����߂�B�܂�cos
	if (ip < DegToRad(30.0f))
		return;

	//Memo Player�̌����́Arotation.y
	// 30�x�����W�A���ɂ���ɂ́ADegToRad(30.0f)
	// �������̂ŁA������ɋ߂Â�
	rotation.y = atan2(dist.x, dist.z);
	forward = VGet(0, 0, 1) * MGetRotY(rotation.y);
	position += forward * 500.0f * Time::DeltaTime();
}
