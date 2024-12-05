#include "Score.h"

Score::Score()
{
	score = 0;
	viewScore = 0;
}

Score::~Score()
{
}

void Score::Update()
{
	if (viewScore < score) {
		viewScore += 1;
	}
}

void Score::Draw()
{
	DrawFormatString(600, 0, GetColor(255, 255, 255), "SCORE=%7d", viewScore);
}

void Score::Add(int val)
{
	score += val;
}
