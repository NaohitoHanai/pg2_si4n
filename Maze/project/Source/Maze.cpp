#include "Maze.h"
#include <time.h>
#include <list>
#include <vector>

const int WIDTH = 51; // 奇数にする
const int HEIGHT = 31; // 奇数にする
struct WALL {
	bool wall;
	bool walking;
	bool checked;
	int checkDir;
};
WALL maze[HEIGHT][WIDTH];
struct IVECTOR {
	int x, y;
	IVECTOR(int _x, int _y) { x = _x; y = _y; }
};
std::list<IVECTOR> walked;
int timer = 0;

void Make1() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			maze[y][x].wall = false;
			maze[y][x].walking = false;
			maze[y][x].checked = false;
			maze[y][x].checkDir = 0;
		}
	}
			// 外周
	for (int x = 0; x < WIDTH; x++) {
		maze[0][x].wall = true;
		maze[HEIGHT-1][x].wall = true;
	}
	for (int y = 0; y < HEIGHT; y++) {
		maze[y][0].wall = true;
		maze[y][WIDTH - 1].wall = true;
	}

	for (int y = 0; y < HEIGHT; y += 2) {
		for (int x = 0; x < WIDTH; x += 2) {
			maze[y][x].wall = true;
		}
	}
	for (int y = 2; y < HEIGHT-1; y += 2) {
		for (int x = 2; x < WIDTH-1; x += 2) {
			while(true) {
				int dir = rand()%4;
				if (y != 2) {
					dir = rand()%3+1; // 上を出さない
				}
				int nextX = x;
				int nextY = y;
				switch(dir) {
				case 0:
					nextX -= 1;
					break;
				case 1:
					nextX += 1;
					break;
				case 2:
					nextY -= 1;
					break;
				case 3:
					nextY += 1;
					break;
				}
				if (maze[nextY][nextX].wall == false) {
					maze[nextY][nextX].wall = true;
					break;
				}
			}
		}
	}
}

void Make2()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			maze[y][x].wall = false;
			maze[y][x].walking = false;
			maze[y][x].checked = false;
			maze[y][x].checkDir = 0;
		}
	}
	// 外周
	for (int x = 0; x < WIDTH; x++) {
		maze[0][x].wall = true;
		maze[HEIGHT - 1][x].wall = true;
	}
	for (int y = 0; y < HEIGHT; y++) {
		maze[y][0].wall = true;
		maze[y][WIDTH - 1].wall = true;
	}
	for (int i=0; i<1000; i++) {
		int startX;
		int startY;
		for (int i=0; i<1000; i++) {
			startX = rand() % (WIDTH/2) * 2;
			startY = rand() % (HEIGHT/2) * 2;
			if (maze[startY][startX].wall) {
				break;
			}
		}
		while (true) {
			std::vector<IVECTOR> canMove;
			IVECTOR move[] = {{2,0}, {-2,0}, {0,2}, {0,-2}};
			for (auto m : move) {
				if (startX+m.x<0 || startX+m.x>=WIDTH)
					continue;
				if (startY + m.y < 0 || startY + m.y >= HEIGHT)
					continue;
				if (maze[startY+m.y][startX+m.x].wall==false) {
					canMove.push_back(m);
				}
			}
			if (canMove.empty()) { // 行き先がない
				break;
			} else {
				int r = rand() % canMove.size();
				startX += canMove[r].x/2;
				startY += canMove[r].y/2;
				maze[startY][startX].wall = true;
				startX += canMove[r].x / 2;
				startY += canMove[r].y / 2;
				maze[startY][startX].wall = true;
			}
		}
	}
}

Maze::Maze()
{
	Make1();
	Make2();
	walked.clear();
	walked.push_back(IVECTOR(1,1));
	maze[1][1].walking = true;
	timer = 0;
}

Maze::~Maze()
{
}

void Maze::Update()
{
//	timer++;
//	if (timer <10) {
//		return;
//	}
//	timer = 0;
	IVECTOR last = *walked.rbegin(); // 最後のマス
	if (last.x==WIDTH-2 && last.y==HEIGHT-2)
		return;
	IVECTOR next = IVECTOR(0,0);
	switch(maze[last.y][last.x].checkDir) {
	case 0:
		next = IVECTOR(last.x - 1, last.y);
		break;
	case 1:
		next = IVECTOR(last.x, last.y - 1);
		break;
	case 2:
		next = IVECTOR(last.x, last.y + 1);
		break;
	case 3:
		next = IVECTOR(last.x + 1, last.y);
		break;
	}
	bool canWalk = true;
	if (maze[next.y][next.x].wall)
		canWalk = false;
	if (maze[next.y][next.x].walking)
		canWalk = false;
	if (maze[next.y][next.x].checked)
		canWalk = false;
	if (canWalk) {
		maze[next.y][next.x].walking = true;
		walked.push_back(next);
	} else {
	IVECTOR next = IVECTOR(0,0);
		maze[last.y][last.x].checkDir++;
		if (maze[last.y][last.x].checkDir >3) { // ここは進めなかった
			walked.pop_back();
			maze[last.y][last.x].walking = false;
			maze[last.y][last.x].checked = true;
		}
	}
}

void Maze::Draw()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x =0; x < WIDTH; x++) {
			if (maze[y][x].wall>0) {
				DrawBox(x*20, y*20, (x+1)*20, (y+1)*20,
					GetColor(255,255,0), TRUE);
			}
		}
	}
	for (auto v : walked) {
		DrawBox(v.x*20, v.y*20, (v.x+1)*20, (v.y+1)*20,
			GetColor(0,0,255), TRUE);
	}
}
