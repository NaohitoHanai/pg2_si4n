#pragma once
#include "../Library/GameObject.h"

class Ground : public GameObject
{
public:
	Ground();
	~Ground();
	void Draw() override;

	/// <summary>
	/// posのXZ地点の地面の高さを求める
	/// </summary>
	/// <param name="pos">調べる座標</param>
	/// <returns>地面の高さ（地面がなかったら-10000を返す）</returns>
	float GetHeight(VECTOR pos);
private:
	int hModel;
};