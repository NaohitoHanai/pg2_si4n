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
		int dy; // Y�̕\������
	};
	static const int H = 10;
	static const int W = 20;
	Cell cells[H+2][W+2]; // �O�����܂�

	/// <summary>
	/// �w�肵���}�X�̂S�����ɓ����F�����邩���ׂāA
	/// �����F�ł���΁A���̃}�X��checkColor���Ă�
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="color"></param>
	/// <returns>�Ȃ����Ă��鐔</returns>
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
