#pragma once
// Pocket.h
#include "../Library/gameObject.h"

class Pocket : public GameObject {
public:
	Pocket();
	~Pocket();
	void Draw() override;

	/// <summary>
	/// ポケットに入ったか判定
	/// </summary>
	/// <param name="bPos"></param>
	/// <param name="bRadius"></param>
	/// <returns>入ったらtrueを返す</returns>
	bool BallIn(VECTOR bPos, float bRadius);

private:
	VECTOR position;
	float radius;
};
