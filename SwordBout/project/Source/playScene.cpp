#include "PlayScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Screen.h"
#include "../Library/Time.h"
#include "Player.h"
#include "Goblin.h"
#include "Axis.h"
#include "Stage.h"
#include "StageObj.h"
#include "csvReader.h"

PlayScene::PlayScene()
{
	Instantiate<Axis>();
	Instantiate<Player>();
//	Instantiate<Goblin>();
	Instantiate<Stage>();

	CsvReader* csv = new CsvReader("data/stage00.csv");
	for (int line = 0; line < csv->GetLines(); line++) {
		std::string category = csv->GetString(line, 0);
		if (category == "OBJ") {
			StageObj* obj = Instantiate<StageObj>();
			obj->LoadModel(csv->GetInt(line, 1));
			float posx = csv->GetFloat(line, 2);
			float posy = csv->GetFloat(line, 3);
			float posz = csv->GetFloat(line, 4);
			obj->SetPosition(posx, posy, posz);
			float rotx = csv->GetFloat(line, 5);
			float roty = csv->GetFloat(line, 6);
			float rotz = csv->GetFloat(line, 7);
			obj->SetRotation(rotx, roty, rotz);
			float scax = csv->GetFloat(line, 8);
			float scay = csv->GetFloat(line, 9);
			float scaz = csv->GetFloat(line, 10);
			obj->SetScale(scax, scay, scaz);
		}
		else if (category == "CHARA") {
			Goblin* gob = Instantiate<Goblin>();
			float posx = csv->GetFloat(line, 2);
			float posy = csv->GetFloat(line, 3);
			float posz = csv->GetFloat(line, 4);
			gob->SetPosition(posx, posy, posz);
		}
	}
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 255, 255), "DeltaTime=%2.2fms", (Time::DeltaTime() * 1000.0f));
}
