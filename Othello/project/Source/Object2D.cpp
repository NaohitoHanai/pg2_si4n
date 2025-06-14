#include "Object2D.h"

void Object2D::Draw()
{
	if (hImage > 0) {
		DrawGraph((int)position.x, (int)position.y, hImage, TRUE);
	}
}
