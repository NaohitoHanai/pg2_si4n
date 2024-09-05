#pragma once
#include "../Library/GameObject.h"

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Update();
	void Draw();
private:
	enum Color {
		NONE = -1,
		RED = 0,
		BLUE,
		GREEN,
		YELLOW,
		MAX
	};
	struct Cell {
		Color color;
		bool selected;
		int dy; // Yの表示差分
	};
	static const int H = 10;
	static const int W = 20;
	Cell cells[H+2][W+2]; // 外周も含む

	/// <summary>
	/// 指定したマスの４方向に同じ色があるか調べて、
	/// 同じ色であれば、そのマスでcheckColorを呼ぶ
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="color"></param>
	/// <returns>つながっている数</returns>
	int checkColor(int x, int y, int color);

	enum State {
		sINPUT = 0,
		sFALL,
		sMOVE,
	};
	State state;
	void updateFall();
	void updateMove();
};
