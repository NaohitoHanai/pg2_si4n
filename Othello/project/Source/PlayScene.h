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
		BLACK_START, // ���̔Ԃł�
		BLACK_TURN,  // ���̑I��҂�
		BLACK_PASS,  // ���̓p�X�ł�
		WHITE_START, // ���̔Ԃł�
		WHITE_TURN,  // ���̑I��҂�
		WHITE_PASS,  // ���̓p�X�ł�
		GAME_OVER,   // ���Ғu���܂���
	};
	State state;
private:
	float timer; // �\�����Ԃ��v��^�C�}�[
};
