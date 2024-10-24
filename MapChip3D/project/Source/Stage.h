#pragma once
//Stage.h
#include "../Library/GameObject.h"
#include "SphereCollider.h"

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
};