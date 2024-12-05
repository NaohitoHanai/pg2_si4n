#include "TitleScene.h"
#include <DxLib.h>
#include <vector>
#include <algorithm>

TitleScene::TitleScene()
{

	RANK r1 = { 1000, "ABC" };
	score.push_back(r1);
	RANK r2 = { 100, "DEF" };
	score.push_back(r2);
	RANK r3 = { 800, "GHI" };
	score.push_back(r3);
	RANK r4 = { 500, "JKL" };
	score.push_back(r4);
	RANK r5 = { 2000, "MNO" };
	score.push_back(r5);
	RANK r6 = { 10, "PQR" };
	score.push_back(r6);

	std::vector<RANK> score2 = score;
	score2[2].score = 10000;

	auto algo1 = [](RANK& sL, RANK& sR) {
		return sL.score > sR.score;
	};
	auto algo2 = [](RANK& sL, RANK& sR) {
		return sL.score < sR.score;
		};
	auto algo = (true) ? algo1 : algo2;

	std::sort(score.begin(), score.end(), algo);
#if 0
	// 並べ替え（最大値抜き出し法）
	int size = score.size();
	for (int i = 0; i < size; i++) {
		int id = i;
		int max = score[id];
		for (int j = i; j < size; j++) {
			if (score[j] > max) {
				max = score[j];
				id = j;
			}
		}
		if (id != i) {
			std::swap<int>(score[id], score[i]);
//			int t = score[id];
//			score[id] = score[i];
//			score[i] = t;
		}
	}
#endif
	num = 0;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	auto func = [&](int a) { return num + a; num++; };
	int x = func(1);

	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	DxLib::DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	for (int i = 0; i < score.size(); i++) {
		DrawFormatString(
			200, i * 20 + 100, GetColor(255, 255, 255),
				"%6d %s", score[i].score, score[i].name);
	}
	DxLib::DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
}
