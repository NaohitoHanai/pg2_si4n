#include "TitleScene.h"
#include <DxLib.h>
#include "DataCarrier.h"
#include "DxColor.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	DataCarrier* data = DataCarrier::GetInstance();
	if (CheckHitKey(KEY_INPUT_Q)) {
		data->SetPlayUser(0, true);
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		data->SetPlayUser(0, false);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		data->SetPlayUser(1, true);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		data->SetPlayUser(1, false);
	}

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DrawString(0, 0, "TITLE SCENE", DX_WHITE);
	int fontSize = GetFontSize();
	SetFontSize(80);
	DrawString(450, 150, "REVERSI", DX_WHITE);

	SetFontSize(30);
	DrawString(450, 300, "Black Side", DX_WHITE);
	if (DataCarrier::GetInstance()->IsPlayUser(0))
		DrawString(650, 300, "User", DX_WHITE);
	else
		DrawString(650, 300, "Com", DX_WHITE);
	SetFontSize(16);
	DrawString(650, 340, "[Q]User [W]Com", DX_WHITE);
	SetFontSize(30);
	DrawString(450, 400, "White Side", DX_WHITE);
	if (DataCarrier::GetInstance()->IsPlayUser(1))
		DrawString(650, 400, "User", DX_WHITE);
	else
		DrawString(650, 400, "Com", DX_WHITE);
	SetFontSize(16);
	DrawString(650, 440, "[A]User [S]Com", DX_WHITE);
	SetFontSize(30);

	DrawString(500, 500, "[P]Key To Play", DX_WHITE);
	DrawString(500, 580, "[ESC]Key To Exit", DX_WHITE);

	SetFontSize(fontSize);
}
