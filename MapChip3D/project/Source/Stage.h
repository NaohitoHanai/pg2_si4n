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
	//•Ç‚Æ“–‚Ä‚ÄA‰Ÿ‚µ•Ô‚·Œü‚«‚Æ—Ê‚ğ•Ô‚·
private:
	int hWall; // •Ç‚Ìƒ‚ƒfƒ‹
	const VECTOR& collisionSquare(const VECTOR& pos, SphereCollider* col,
		VECTOR point[4], VECTOR normal);
	std::vector<std::string> map;
};