#pragma once
#include "../Library/SceneBase.h"

class Player;

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:
	Player* player[2];
	enum State {
		START = 0,
		BLACK_START, // 黒の番です
		BLACK_TURN,  // 黒の選択待ち
		BLACK_PASS,  // 黒はパスです
		WHITE_START, // 白の番です
		WHITE_TURN,  // 白の選択待ち
		WHITE_PASS,  // 白はパスです
		GAME_OVER,   // 両者置けません
	};
	State state;
private:
	float timer; // 表示時間を計るタイマー
};
