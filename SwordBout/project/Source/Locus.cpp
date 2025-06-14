#include "Locus.h"
#include <assert.h>
#include <vector>

Locus::Locus()
{
	ObjectManager::SetDrawOrder(this, -100);
	writeP = 0;
	oldestP = 0;

	hImage = LoadGraph("data/Effect/SlashLocus.png");
	assert(hImage > 0);
}

Locus::~Locus()
{
}

void Locus::Update()
{
}

void Locus::Draw()
{
	std::vector<VERTEX3D> vertexes;
	std::vector<unsigned short> indexes;

	VERTEX3D v;
	v.norm = VGet(0, 1, 0);
	v.dif = GetColorU8(255, 255, 0, 255);
	v.spc = GetColorU8(255, 255, 0, 255);
	if (oldestP == writeP) return; // データがない

	int start = (oldestP+1) % KeepNum;
	for (int i = start; i != writeP;
						i = (i + 1) % KeepNum) {
		int p0 = (i + KeepNum - 2) % KeepNum;
		int p1 = (i + KeepNum - 1) % KeepNum;
		int p2 = i;
		int p3 = (i+1) % KeepNum;
		if (i==start) {
			p0 = p1;
		}
		if (i == (writeP+KeepNum-1) % KeepNum) {
			p3 = p2;
		}
		MakeVertexSpline(vertexes, p0, p1, p2, p3);
	}
	//グラデーション(v)を設定する
	float val = 0.0f;
//	for (int i = 0; i < vertexes.size(); i += 2) { // これの逆
	for (int i = vertexes.size() - 2; i >= 0; i -= 2) {
		vertexes[i].v = val;
		vertexes[i+1].v = val;
		val += 1.0f / KeepNum;
	}
	if (vertexes.size() < 4)
		return;
	// indexesを作る
	for (int n = 0; n < vertexes.size()-2; n += 2) {
		indexes.push_back(n + 0);
		indexes.push_back(n + 1);
		indexes.push_back(n + 2);
		indexes.push_back(n + 1);
		indexes.push_back(n + 3);
		indexes.push_back(n + 2);
	}
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	DrawPolygonIndexed3D(&vertexes[0], vertexes.size(),
		&indexes[0], indexes.size() / 3, hImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Locus::Add(VECTOR root, VECTOR tip)
{
	Position p;
	p.root = root;
	p.tip = tip;
	positions[writeP] = p;
	writeP = (writeP + 1) % KeepNum;
	if (writeP == oldestP) {
		oldestP = (oldestP + 1) % KeepNum;
	}
}

void Locus::MakeVertexSpline(std::vector<VERTEX3D>& vt, int p0, int p1, int p2, int p3)
{
	VERTEX3D v;
	v.norm = VGet(0, 1, 0);
	v.dif = GetColorU8(255, 255, 255, 255);
	v.spc = GetColorU8(255, 255, 255, 255);

	// Catmull-ROM補間をする
	// rootとtipのそれぞれで
	// 三次曲線at^3 + bt^2 + ct + dの係数を求める
	VECTOR rV0 = (positions[p2].root - positions[p0].root) / 2.0f; // p1の傾き
	VECTOR rV1 = (positions[p3].root - positions[p1].root) / 2.0f; // p2の傾き
	VECTOR ra = 2 * positions[p1].root - 2 * positions[p2].root
		+ rV0 + rV1;
	VECTOR rb = -3 * positions[p1].root + 3 * positions[p2].root
		- 2 * rV0 - rV1;
	VECTOR rc = rV0;
	VECTOR rd = positions[p1].root;

	VECTOR tV0 = (positions[p2].tip - positions[p0].tip) / 2.0f; // p1の傾き
	VECTOR tV1 = (positions[p3].tip - positions[p1].tip) / 2.0f; // p2の傾き
	VECTOR ta = 2 * positions[p1].tip - 2 * positions[p2].tip
		+ tV0 + tV1;
	VECTOR tb = -3 * positions[p1].tip + 3*positions[p2].tip
		- 2 * tV0 - tV1;
	VECTOR tc = tV0;
	VECTOR td = positions[p1].tip;
	// tを0から1に変化させて、座標を求める
	for (int i = 0; i < 4; i++) {
		float t = (float)i / 4.0f;
		v.pos = ra * t * t * t + rb * t * t + rc * t + rd;
		v.u = 0.0f;
		v.v = 0.0f;
		vt.push_back(v);
		v.pos = ta * t * t * t + tb * t * t + tc * t + td;
		v.u = 1.0f;
		v.v = 0.0f;
		vt.push_back(v);
	}
}
