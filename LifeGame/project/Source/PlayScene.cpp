#include "PlayScene.h"

class Player : public GameObject {
};

PlayScene::PlayScene()
{
	new Player();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	Player* p = FindGameObject<Player>();

	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
