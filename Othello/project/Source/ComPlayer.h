#pragma once
#include "Player.h"

/// <summary>
/// Player�N���X���p�����āA�}�X��I�����镔����AI�ɂ���
/// </summary>
class ComPlayer : public Player {
public:
	ComPlayer(Board::Face color) : Player(color) {}
	~ComPlayer() {}
private:
	/// <summary>
	/// AI�Ń}�X��I������
	/// </summary>
	/// <returns>�I�������}�X</returns>
	IVector2 SelectCell() override;
};