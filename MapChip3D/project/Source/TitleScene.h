#pragma once
#include "../Library/SceneBase.h"
#include <vector>

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
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
