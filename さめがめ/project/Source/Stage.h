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
	};
	struct Cell {
		Color color;
	};
	static const int H = 3;
	static const int W = 2;
	Cell cells[H+2][W+2]; // ŠOŽü‚àŠÜ‚Þ
};
