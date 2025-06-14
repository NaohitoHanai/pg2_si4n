#include "Life.h"
#include <string>
using namespace std;

static const int WIDTH = 60;
static const int HEIGHT = 50;

vector<string> map = {
	"                    ",
	"                    ",
	"                    ",
	"                    ",
	"                              S",
	"                            S S",
	"                  SS      SS            SS",
	"                 S   S    SS            SS",
	"      SS        S     S   SS",
	"      SS        S   S SS    S S",
	"                S     S       S",
	"                 S   S",
	"                  SS",
	"                  ",
	"                  ",
	"                  ",
};

Life::Life()
{
	for (int y = 0; y < HEIGHT; y++) {
		vector<Cell> line;
		for (int x = 0; x < WIDTH; x++) {
			Cell c = { false, false };
			line.push_back(c);
		}
		cells.push_back(line);
	}
	for (int y = 0; y < map.size(); y++) {
		for (int x = 0; x < map[y].size(); x++) {
			if (map[y][x] == 'S')
				cells[y+1][x+1].alive = true;
		}
	}
	count = 0;
}

Life::~Life()
{
}

void Life::Update()
{
	if (++count<5)
		return;
	count = 0;
	for (int y = 1; y < cells.size()-1; y++) {
		for (int x = 1; x < cells[y].size()-1; x++) {
			if (!cells[y][x].alive) {
				if (RoundCount(x, y) == 3) {
					cells[y][x].next = true;
				} else {
					cells[y][x].next = false;
				}
			} else {
				int c = RoundCount(x, y);
				if (c == 2 || c == 3) {
					cells[y][x].next = true;
				} else {
					cells[y][x].next = false;
				}
			}
		}
	}
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			cells[y][x].alive = cells[y][x].next;
		}
	}
}

void Life::Draw()
{
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			if (cells[y][x].alive) {
				DrawBox(x * 20, y * 20, (x + 1) * 20, (y + 1) * 20, GetColor(255, 255, 255), TRUE);
			}
		}
	}
}

int Life::RoundCount(int x, int y)
{
	int c = 0;
	if (cells[y+1][x-1].alive) c++;
	if (cells[y  ][x-1].alive) c++;
	if (cells[y-1][x-1].alive) c++;
	if (cells[y+1][x  ].alive) c++;
	if (cells[y-1][x  ].alive) c++;
	if (cells[y+1][x+1].alive) c++;
	if (cells[y  ][x+1].alive) c++;
	if (cells[y-1][x+1].alive) c++;
	return c;
}
