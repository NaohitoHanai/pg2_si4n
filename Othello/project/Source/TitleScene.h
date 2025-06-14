#pragma once
#include "../Library/SceneBase.h"

#include "Object2D.h"
#include "Board.h"
class Button;

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
};
