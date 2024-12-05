#pragma once
#include "../Library/GameObject.h"

// Locus.h
// 剣の軌跡を表示する

class Locus : public GameObject {
public:
	Locus();
	~Locus();
	void Update();
	void Draw();

	/// <summary>
	/// 剣の位置を追加する
	/// </summary>
	/// <param name="root">柄の座標</param>
	/// <param name="tip">剣先の座標</param>
	void Add(VECTOR root, VECTOR tip);
};