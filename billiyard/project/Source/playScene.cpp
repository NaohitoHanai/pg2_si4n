#include "playScene.h"
#include "../Library/sceneManager.h"
#include <DxLib.h>
#include "BallManager.h"
#include "Pocket.h"

PlayScene::PlayScene()
{
	Instantiate<Pocket>();
	Instantiate<BallManager>();	
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	SceneBase::Draw();

	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
