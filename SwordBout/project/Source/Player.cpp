#include "Player.h"
#include "Stage.h"
#include "../Library/Time.h"
#include "../ImGui/imgui.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);

	//仮に、ここに書いておく
	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -500), VGet(0, 0, 0));
}

Player::~Player()
{
}

void Player::Start()
{
}

//float PI = 3.141592653589793238462643383279;
void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		//position.z += cosf(rotation.y) * 2.0f;
		//position.x += sinf(rotation.y) * 2.0f;

		MATRIX rotY = MGetRotY(rotation.y); // 回転行列を作る
		VECTOR move = VGet(0, 0, 2);  // 回転してない時の移動ベクトル
		VECTOR forward = move * rotY; // 回転行列を掛けるとforward
		position += forward;
		// Unityっぽく書くなら
		//MATRIX rotY = MGetRotY(rotation.y); // 回転行列を作る
		//VECTOR move = VGet(0, 0, 1);  // 回転してない時の長さ１のベクトル
		//VECTOR forward = move * rotY; // 回転行列を掛けるとforward
		//position += forward * 2.0f; // ここで速度を掛ける
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		rotation.y += 3.0f * DX_PI_F / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		rotation.y -= 3.0f * DX_PI_F / 180.0f;
	}
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
	VECTOR cameraPos = 
		VGet(0, 300, -500) * MGetRotY(rotation.y) * MGetTranslate(position);
	SetCameraPositionAndTarget_UpVecY( cameraPos, position );

//変数を見たいので
	ImGui::Begin("Player");
	ImGui::InputFloat("X", &position.x);
	ImGui::InputFloat("Y", &position.y);
	ImGui::InputFloat("Z", &position.z);
	ImGui::End();
}

void Player::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}