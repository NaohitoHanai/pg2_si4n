#pragma once
//Stage.h
#include "../Library/GameObject.h"
#include "SphereCollider.h"
#include <string>
#include <vector>

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Update() override;
	void Draw() override;
	const VECTOR& CollisionSphere(const VECTOR& pos, SphereCollider* col);
	//壁と当てて、押し返す向きと量を返す
private:
	int hWall; // 壁のモデル
	const VECTOR& collisionSquare(const VECTOR& pos, SphereCollider* col,
		VECTOR point[4], VECTOR normal);
	std::vector<std::string> map;
};