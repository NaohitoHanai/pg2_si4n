#include "ComPlayer.h"

IVector2 ComPlayer::SelectCell()
{
	Board* board = FindGameObject<Board>();
	IVector2 pos = IVector2(0, 0);
	int max = 0;
	for (int y = 0; y < Board::HEIGHT; y++) {
		for (int x = 0; x < Board::WIDTH; x++) {
			int num = board->CheckPut(IVector2(x, y), myColor);
			if (num > max) {
				pos = IVector2(x, y);
				max = num;
			}
		}
	}
	return pos;
}
