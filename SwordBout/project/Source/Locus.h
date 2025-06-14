#pragma once
#include "../Library/GameObject.h"
#include <vector>

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
private:
	static const int KeepNum = 20;
	struct Position {
		VECTOR root;
		VECTOR tip;
	};
	Position positions[KeepNum];
	int writeP;  // 次に書く場所
	int oldestP; // 一番古い場所

	int hImage; // 画像ファイル

	void MakeVertexSpline(std::vector<VERTEX3D>& vt, int p0, int p1, int p2, int p3);
};