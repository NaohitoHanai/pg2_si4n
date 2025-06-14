#include "PlayScene.h"
#include <DxLib.h>
#include "Board.h"
#include "ComPlayer.h"
#include "../Library/time.h"
#include "DxColor.h"
#include "DataCarrier.h"

namespace {
	static const float WAIT_TIME = 1.0f;
};

PlayScene::PlayScene()
{
	new Board();
	DataCarrier* data = DataCarrier::GetInstance();
	for (int i = 0; i < Board::Face::MAX; i++) {
		if (data->IsPlayUser(i)) {
			player[i] = new Player((Board::Face)i);
		}
		else {
			player[i] = new ComPlayer((Board::Face)i);
		}
	}
	state = START;
	timer = WAIT_TIME; // 表示時間
}

PlayScene::~PlayScene()
{
}

int getX(float timer) {
	if (timer < WAIT_TIME-0.5f)
		return 800;
	else
		return 800 + (int)(0.5f - (WAIT_TIME - timer)) * 1000;
}

void PlayScene::Update()
{
	switch (state) {
	case START:
		timer -= Time::DeltaTime();
		if (timer <= 0.0f) {
			timer = WAIT_TIME;
			state = BLACK_START;
		}
		break;
	case BLACK_START:
		if (!player[0]->CanPut()) {
			if (!player[1]->CanPut()) {
				state = GAME_OVER;
			}
			else {
				state = BLACK_PASS;
			}
		}
		timer -= Time::DeltaTime();
		if (timer <= 0.0f) {
			player[0]->TurnStart();
			state = BLACK_TURN;
		}
		break;
	case BLACK_TURN:
		if (player[0]->TurnEnd()) {
			timer = WAIT_TIME;
			state = WHITE_START;
		}
		break;
	case BLACK_PASS:
		timer -= Time::DeltaTime();
		if (timer <= 0.0f) {
			timer = WAIT_TIME;
			state = WHITE_START;
		}
		break;
	case WHITE_START:
		if (!player[1]->CanPut()) {
			if (!player[0]->CanPut()) {
				state = GAME_OVER;
			}
			else {
				state = WHITE_PASS;
			}
		}
		timer -= Time::DeltaTime();
		if (timer <= 0.0f) {
			player[1]->TurnStart();
			state = WHITE_TURN;
		}
		break;
	case WHITE_TURN:
		if (player[1]->TurnEnd()) {
			timer = WAIT_TIME;
			state = BLACK_START;
		}
		break;
	case WHITE_PASS:
		timer -= Time::DeltaTime();
		if (timer <= 0.0f) {
			timer = WAIT_TIME;
			state = BLACK_START;
		}
		break;
	case GAME_OVER:
		timer = 0.0f;
		break;
	}

	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	static const char* text[] = {
		"試合開始",
		"黒のばんです",
		"黒を置くマスを選んでください",
		"黒は置くことができません",
		"白のばんです",
		"白を置くマスを選んでください",
		"白は置くことができません",
		"試合終了です",
	};
	DrawString(getX(timer), 200, text[state], DX_WHITE);
//	DrawString(0, 0, "PLAY SCENE", DX_WHITE);
//	DrawString(100, 400, "Push [T]Key To Title", DX_WHITE);
}
