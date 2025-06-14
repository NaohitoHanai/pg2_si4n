#pragma once
#include "Player.h"

/// <summary>
/// Playerクラスを継承して、マスを選択する部分をAIにする
/// </summary>
class ComPlayer : public Player {
public:
	ComPlayer(Board::Face color) : Player(color) {}
	~ComPlayer() {}
private:
	/// <summary>
	/// AIでマスを選択する
	/// </summary>
	/// <returns>選択したマス</returns>
	IVector2 SelectCell() override;
};