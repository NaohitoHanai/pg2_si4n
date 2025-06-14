#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PlayScene");
	}
	if (CheckHitKey(KEY_INPUT_B)) {
		SceneManager::ChangeScene("BossScene");
	}

	SceneBase::Update();
}


void TitleScene::Draw()
{
	SceneBase::Draw();
	DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
