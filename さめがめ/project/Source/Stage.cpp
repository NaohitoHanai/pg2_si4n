#include "Stage.h"

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
		}
	}
	for (int y = 1; y < H+1; y++) {
		for (int x = 1; x < W+1; x++) {
			cells[y][x].color = RED;
		}
	}
	cells[1][1].color = BLUE;
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Draw()
{
	for (int y = 1; y < H+1; y++) {
		for (int x = 1; x < W+1; x++) {
			int c = cells[y][x].color;
			if (c == NONE)
				continue;
			DrawCircle((x-1) * 40 + 30, (H-y) * 40 + 30, 20,
				rgb[c], TRUE);
		}
	}
}
