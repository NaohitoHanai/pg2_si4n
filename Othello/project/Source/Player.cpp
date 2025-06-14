#include "Player.h"
#include "DxColor.h"

Player::Player(Board::Face color)
{
	myColor = color;
	state = WAIT;
	canPut = false;
}

Player::~Player()
{
}

void Player::Update()
{
	if (state == WAIT) return;

	Board* board = FindGameObject<Board>();
	IVector2 sel = SelectCell();
	if (sel.x >= 0 && sel.y >= 0) {
		board->Put(sel, myColor);
		state = WAIT;
		canPut = false;
		board->CursorOff();
	}
}

void Player::Draw()
{
	if (canPut) {
		DrawString(800, 300, "‚¨‚¯‚Ü‚·‚æ", DX_WHITE);
	}
}

void Player::TurnStart()
{
	state = SELECT;
}

bool Player::TurnEnd()
{
	return (state == WAIT);
}

bool Player::CanPut()
{
	Board* board = FindGameObject<Board>();
	if (board->IsPass(myColor))
		return false;
	return true;
}

IVector2 Player::SelectCell()
{
	Board* board = FindGameObject<Board>();

	canPut = false;

	IVector2 sel;
	GetMousePoint(&sel.x, &sel.y);
	sel = board->GetCellPosition(sel);
	board->DrawCursor(sel);
	if (sel.x >= 0 && sel.y >= 0) {
		if (board->CheckPut(sel, myColor) > 0) {
			canPut = true;
			if (GetMouseInput() & MOUSE_INPUT_LEFT) {
				return sel;
			}
		}
	}
	return IVector2(-1, -1);
}
