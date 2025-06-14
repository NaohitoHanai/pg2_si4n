#pragma once
// Pocket.h
#include "../Library/gameObject.h"

class Pocket : public GameObject {
public:
	Pocket();
	~Pocket();
	void Draw() override;

	/// <summary>
	/// �|�P�b�g�ɓ�����������
	/// </summary>
	/// <param name="bPos"></param>
	/// <param name="bRadius"></param>
	/// <returns>��������true��Ԃ�</returns>
	bool BallIn(VECTOR bPos, float bRadius);

private:
	VECTOR position;
	float radius;
};
