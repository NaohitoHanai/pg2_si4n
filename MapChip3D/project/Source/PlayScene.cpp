#include "PlayScene.h"
#include <DxLib.h>
#include "Stage.h"
#include "SaveLoad.h"
#include "Score.h"

PlayScene::PlayScene()
{
	new Stage();
	new Score();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_K)) {
		SaveLoad save;
		save.Save();
	}
	if (CheckHitKey(KEY_INPUT_L)) {
		SaveLoad load;
		load.Load();
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
