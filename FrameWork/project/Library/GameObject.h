#pragma once
#include <DxLib.h>

class GameObject {
public:
	GameObject();
	virtual ~GameObject() {}
	virtual void Update() {}
	virtual void Draw() {}
	void DestroyMe();
	bool IsDestroy() {
		return destroy;
	}
private:
	bool destroy;
};