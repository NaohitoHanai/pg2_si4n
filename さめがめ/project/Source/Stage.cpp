#include "Stage.h"
#include "../ImGui/imgui.h"

namespace {
	static const int rgb[] = {
		GetColor(255, 0, 0),
		GetColor(0, 255, 0),
		GetColor(0, 0, 255),
		GetColor(255, 0, 255),
	};
};


Stage::Stage()
{
	for (int y = 0; y < H + 2; y++) {
		for (int x = 0; x < W + 2; x++) {
			cells[y][x].color = NONE;
			cells[y][x].selected = false;
			cells[y][x].dy = 0;
		}
	}
	for (int y = 1; y < H+1; y++) {
		for (int x = 1; x < W+1; x++) {
			cells[y][x].color = (Color)GetRand(MAX-1);
		}
	}
	state = sINPUT;
}

Stage::~Stage()
{
}

void Stage::Update()
{
	if (state == sFALL) {
		updateFall();
		return;
	}
	else if (state == sMOVE) {
		updateMove();
		return;
	}
	for (int y = 0; y < H + 2; y++) {
		for (int x = 0; x < W + 2; x++) {
			cells[y][x].selected = false;
		}
	}
	int mx, my;
	GetMousePoint(&mx, &my);
	ImGui::Begin("MousePosition");
	ImGui::InputInt("X", &mx);
	ImGui::InputInt("Y", &my);
	ImGui::End();
	// マウスカーソルが刺した場所のselectedをfalse
	int x = (mx - 10) / 40 + 1; // 表示の計算式の逆
	int y = -((my-10)/40-H);
	if (x >= 1 && x <= W && y >= 1 && y <= H) {
		// つながっているものをすべて、selected=trueにする
		int connect = checkColor(x, y, cells[y][x].color);
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			// ２つ以上つながっていれば消す
			if (connect >= 2) {
				for (int y = 1; y <= H; y++) {
					for (int x = 1; x <= W; x++) {
						if (cells[y][x].selected) {
							cells[y][x].color = NONE;
						}
					}
				}
				// 落下処理
				for (int x = 1; x <= W; x++) {
					int erased = 0;
					for (int y = 1; y <= H; y++) {
						if (cells[y][x].color == NONE) {
							erased++;
						}
						else {
							if (erased > 0) {
								cells[y - erased][x] = cells[y][x];
								cells[y - erased][x].dy = erased*40;
							}
						}
					}
					for (int y2 = 0; y2 < erased; y2++) {
						cells[H - y2][x].color = NONE;
					}
				}
				state = sFALL;
			}
		}
	}
}

void Stage::Draw()
{
	for (int y = 1; y <= H; y++) {
		for (int x = 1; x <= W; x++) {
			int c = cells[y][x].color;
			if (c == NONE)
				continue;
			if (cells[y][x].selected) {
				DrawCircle((x - 1) * 40 + 30, (H - y) * 40 + 30 - cells[y][x].dy, 20,
					rgb[c], FALSE);
			}
			else {
				DrawCircle((x - 1) * 40 + 30, (H - y) * 40 + 30 - cells[y][x].dy, 20,
					rgb[c], TRUE);
			}
		}
	}
}

int Stage::checkColor(int x, int y, int color)
{
	if (cells[y][x].selected)
		return 0;
	if (cells[y][x].color!=color)
		return 0;
	cells[y][x].selected = true;
	int ret = 1;
	ret += checkColor(x + 1, y, color);
	ret += checkColor(x - 1, y, color);
	ret += checkColor(x, y+1, color);
	ret += checkColor(x, y-1, color);
	return ret;
}

void Stage::updateFall()
{
	// cellsのdy>0があれば、dyを減らす
	// すべてのdyが0になったら、state=sINPUTにする
}

void Stage::updateMove()
{
}
