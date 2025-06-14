#pragma once
#include "../Library/GameObject.h"
#include <vector>
using namespace std;

class Life : public GameObject
{
public:
	Life();
	~Life();
	void Update() override;
	void Draw() override;
private:
	struct Cell {
		bool alive;
		bool next;
	};
	vector<vector<Cell>> cells;
	int RoundCount(int x, int y);
	int count;
};