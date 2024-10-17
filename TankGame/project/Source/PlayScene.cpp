#include "PlayScene.h"
#include <DxLib.h>
#include "Tank.h"
#include "Ground.h"
#include "Target.h"
PlayScene::PlayScene()
{
	new Tank();
	new Ground();
	new Target(VGet(0, 100, 600));
	new Target(VGet(300, 100, 600));
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
