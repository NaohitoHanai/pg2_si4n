#pragma once
#include "../Library/SceneBase.h"
#include <vector>

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	int num;
	struct RANK {
		int score;
		const char* name;
	};
	std::vector<RANK> score;
};
