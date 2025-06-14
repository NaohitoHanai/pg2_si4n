#pragma once
#include "Object2D.h"
#include "Board.h"

/// <summary>
/// プレイヤーの処理を行う
/// </summary>
class Player : public Object2D {
public:
	Player(Board::Face color);
	virtual ~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// 自分のターンになった
	/// </summary>
	void TurnStart();

	/// <summary>
	/// 自分のターンが終了したかを返す
	/// </summary>
	/// <returns>ターン終了したらtrue</returns>
	bool TurnEnd();

	/// <summary>
	/// 自分のコマが置けるかを調べる
	/// </summary>
	/// <returns>置ける場合はtrue</returns>
	bool CanPut();
private:

	/// <summary>
	/// 自分のターンの処理をする
	/// マウス入力を見て、マスを選択する
	/// Comプレイヤーは、ここを継承して、AIでマスを選択する
	/// </summary>
	/// <returns>選択したマス</returns>
	virtual IVector2 SelectCell();
protected:
	Board::Face myColor; // 自分の色
private:
	enum State {
		WAIT = 0, // プレイ待ち
		SELECT,   // 選択中
	};
	State state;

	bool canPut; // 自分のコマが置ける場合に「置けますよ」を表示するため
};