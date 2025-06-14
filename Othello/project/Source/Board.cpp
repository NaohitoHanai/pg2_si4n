#include "Board.h"
#include "Screen.h"
#include "DxColor.h"

namespace {
	static const int DISK_RADIUS = 28;
	static const int CELL_SIZE = DISK_RADIUS * 2 + 8;
	static const unsigned int BoardColor = GetColor(0,128, 0);
};

Board::Board()
{
	position = IVector2(250, 30);

	// 盤面をクリア
	for (int y = 0; y < HEIGHT + 2; y++) {
		for (int x = 0; x < WIDTH + 2; x++) {
			cells[y][x] = Face::NODISC;
		}
	}
	Put(IVector2(3, 3), Face::BLACK);
	Put(IVector2(3, 4), Face::WHITE);
	Put(IVector2(4, 3), Face::WHITE);
	Put(IVector2(4, 4), Face::BLACK);

	CursorOff();
}

Board::~Board()
{
}

void Board::Update()
{
}

void Board::Draw()
{
	DrawBox(position.x, position.y, position.x+CELL_SIZE*WIDTH, position.y+CELL_SIZE*HEIGHT,
				BoardColor, TRUE);

	for (int x = 0; x <= WIDTH; x++) {
		DrawLine(position.x + x * CELL_SIZE, position.y, 
			position.x + x * CELL_SIZE, position.y + HEIGHT * CELL_SIZE, 
			DX_BLACK, 2);
	}
	for (int y = 0; y <= HEIGHT; y++) {
		DrawLine(position.x, position.y + y * CELL_SIZE,
			position.x + WIDTH * CELL_SIZE, position.y + y * CELL_SIZE,
			DX_BLACK, 2);
	}
	DrawCircle(position.x + 2 * CELL_SIZE, position.y + 2 * CELL_SIZE, 5, DX_BLACK, TRUE);
	DrawCircle(position.x + 2 * CELL_SIZE, position.y + (HEIGHT - 2) * CELL_SIZE, 5, DX_BLACK, TRUE);
	DrawCircle(position.x + (WIDTH - 2) * CELL_SIZE, position.y + 2 * CELL_SIZE, 5, DX_BLACK, TRUE);
	DrawCircle(position.x + (WIDTH - 2) * CELL_SIZE, position.y + (HEIGHT - 2) * CELL_SIZE, 5, DX_BLACK, TRUE);
	if (cursor.x >= 0 && cursor.y >= 0) {
		DrawBox(position.x + cursor.x * CELL_SIZE, position.y + cursor.y * CELL_SIZE,
			position.x + (cursor.x+1) * CELL_SIZE, position.y + (cursor.y+1) * CELL_SIZE,
			DX_RED, FALSE);
	}


	for (int y = 1; y <= HEIGHT; y++) {
		for (int x = 1; x <= WIDTH; x++) {
			if (cells[y][x] == Face::NODISC)
				continue;
			unsigned int c = (cells[y][x] == Face::BLACK) ? DX_BLACK : DX_WHITE;
			DrawCircle(x * CELL_SIZE - CELL_SIZE / 2 + position.x, y * CELL_SIZE - CELL_SIZE / 2 + position.y,
					DISK_RADIUS, c, TRUE);
		}
	}

	DrawFormatString(800, 500, DX_WHITE, "Black=%2d", GetScore(Face::BLACK));
	DrawFormatString(800, 530, DX_WHITE, "White=%2d", GetScore(Face::WHITE));

}

IVector2 Board::GetCellPosition(IVector2 screenPos)
{
	int x = (screenPos.x - position.x);
	int y = (screenPos.y - position.y);
	if (x < 0 || y < 0)
		return IVector2(-1, -1);
	x /= CELL_SIZE;
	y /= CELL_SIZE;
	if (x >= WIDTH || y >= HEIGHT)
		return IVector2(-1, -1);
	return IVector2(x, y);
}

int Board::CheckPut(IVector2 pos, Face color)
{
	if (pos.x < 0 || pos.x >= WIDTH) { // 盤面の外
		return 0;
	}
	if (pos.y < 0 || pos.y >= HEIGHT) {
		return 0;
	}
	if (cells[pos.y+1][pos.x+1] != Face::NODISC) { // すでに置かれている
		return 0;
	}
	static const IVector2 dirs[] = {
		{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}
	};
	Face other = (color == Face::BLACK) ? Face::WHITE : Face::BLACK;
	int hit = 0;
	for (IVector2 d : dirs) {
		int cx = pos.x+1 + d.x;
		int cy = pos.y+1 + d.y;
		for (int num = 0; num < WIDTH; num++) {
			if (cells[cy][cx] == other) {
				cx += d.x;
				cy += d.y;
				continue;
			}
			if (cells[cy][cx] == color) {
				if(cy==cx || cx==8-cy || cy==8-cx)
					hit += num*4;
				else
					hit += num;
			}
			break;

		}
	}
	return hit;
}

void Board::Put(IVector2 pos, Face color)
{
	if (pos.x < 0 || pos.x >= WIDTH) { // 盤面の外
		return;
	}
	if (pos.y < 0 || pos.y >= HEIGHT) {
		return;
	}
	if (cells[pos.y+1][pos.x+1] != Face::NODISC) { // すでに置かれている
		return;
	}
	static const IVector2 dirs[] = {
		{-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}, {-1,0}
	};
	Face other = (color == Face::BLACK) ? Face::WHITE : Face::BLACK;
	int hit = 0;
	cells[pos.y + 1][pos.x + 1] = color;
	for (IVector2 d : dirs) {
		int cx = pos.x+1 + d.x;
		int cy = pos.y+1 + d.y;
		for (int num = 0; true; num++) {
			if (cells[cy][cx] == other) {
				cx += d.x;
				cy += d.y;
				continue;
			}
			if (cells[cy][cx] == color) {
				for (int n = 1; n <= num; n++) {
					cx = pos.x+1 + d.x * n;
					cy = pos.y+1 + d.y * n;
					cells[cy][cx] = color;
				}
			}
			break;
		}
	}
}

int Board::GetScore(Face color)
{
	int count = 0;

	for (int y = 1; y <= HEIGHT; y++) {
		for (int x = 1; x <= WIDTH; x++) {
			if (cells[y][x] == color)
				count++;
		}
	}
	return count;
}

bool Board::IsPass(Face color)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (CheckPut(IVector2(x, y), color) > 0)
				return false;
		}
	}
	return true;
}

