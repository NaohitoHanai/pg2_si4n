#pragma once
#include "../Library/sceneBase.h"
class Deck;
class PlayerCards;

class PlayScene : public SceneBase {
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

private:
	void handOut();
	bool isHandingOut;

	Deck* deck;
	PlayerCards* player[2];
	int turn;
	int counter;
};