#pragma once
#include "../Library/GameObject.h"

// Locus.h
// ���̋O�Ղ�\������

class Locus : public GameObject {
public:
	Locus();
	~Locus();
	void Update();
	void Draw();

	/// <summary>
	/// ���̈ʒu��ǉ�����
	/// </summary>
	/// <param name="root">���̍��W</param>
	/// <param name="tip">����̍��W</param>
	void Add(VECTOR root, VECTOR tip);
};