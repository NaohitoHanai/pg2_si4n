#pragma once
#include "Object2D.h"

/// <summary>
/// 盤面の管理、置かれているコマの情報を持っている
/// </summary>
class Board : public Object2D {
public:
	Board();
	~Board();
	void Update();
	void Draw();

	/// <summary>
	/// マスに置かれているコマの情報
	/// </summary>
	enum Face {
		NODISC = -1, // 何も置いてない
		BLACK = 0,   // 黒
		WHITE,       // 白
		MAX
	};

	/// <summary>
	/// マウス座標から、マスの位置を特定する
	/// マスの位置が特定できない場合は、(-1,-1)を返す
	/// </summary>
	/// <param name="screen">マウス座標（ウィンドウ内の座標）</param>
	/// <returns>マスの位置</returns>
	IVector2 GetCellPosition(IVector2 screen);

	/// <summary>
	/// このマスに置けるか確認する
	/// </summary>
	/// <param name="pos">マスの位置</param>
	/// <param name="color">置く予定のコマの色</param>
	/// <returns>ひっくり返す数（置けない場合は0）</returns>
	int CheckPut(IVector2 pos, Face color);

	/// <summary>
	/// マスにコマを置く
	/// </summary>
	/// <param name="pos">マスの位置</param>
	/// <param name="color">置くコマの色</param>
	void Put(IVector2 pos, Face color);

	/// <summary>
	/// 指定した色のコマの数を返す
	/// </summary>
	/// <param name="color">置くコマの色</param>
	/// <returns>自分のコマの数</returns>
	int GetScore(Face color);

	/// <summary>
	/// パスするかを調べる
	/// </summary>
	/// <param name="color">置くコマの色</param>
	/// <returns>置ける場所がなければtrue</returns>
	bool IsPass(Face color);

	/// <summary>
	/// カーソル（赤枠）を表示する
	/// </summary>
	/// <param name="pos">カーソルを表示するマスの位置</param>
	void DrawCursor(IVector2 pos) {
		cursor = pos;
	};

	/// <summary>
	/// カーソル（赤枠）を消す
	/// </summary>
	void CursorOff() {
		cursor = IVector2(-1, -1);
	}

	static const int WIDTH = 8;  // 盤面の幅
	static const int HEIGHT = 8; // 盤面の高さ
private:
	Face cells[HEIGHT + 2][WIDTH + 2]; // 盤面情報（外側に１つ余計に取る）
	IVector2 cursor; // カーソルの位置
	IVector2 position; // 盤の位置
};