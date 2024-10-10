#pragma once
#include <DxLib.h>
#include "ObjectManager.h"

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
	template<class C> C* FindGameObject()
	{
		return ObjectManager::GetInst()->FindGameObject();
	}

	template<class C> std::list<C*> FindGameObjects()
	{
		return ObjectManager::GetInst()->FindGameObjects();
	}
private:
	bool destroy;
};

