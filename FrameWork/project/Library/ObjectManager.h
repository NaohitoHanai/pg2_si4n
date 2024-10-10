#pragma once
//ObjectManager.h
// どこからでも呼べるクラスの作り方
// ①Cの関数
// ②シングルトン
// ③namespaceで囲む
// ④インスタンスをグローバルにする
// 今回はシングルトンで書く
#include <list>
class GameObject;

class ObjectManager {
public:
	static ObjectManager* GetInst() { // GetInst()はstaticにする
		static ObjectManager* instance = nullptr; // クラス内に自分のインスタンスを持つ
		if (instance == nullptr) {
			instance = new ObjectManager();
		}
		return instance;
	}
	void Init();
	void Update();
	void Draw();
	void Release();
	/// <summary>
	/// objをobjectsに追加する
	/// </summary>
	/// <param name="obj"></param>
	void Push(GameObject* obj);

	/// <summary>
	/// objectsから削除する
	/// </summary>
	/// <param name="obj"></param>
	void Pop(GameObject* obj);

	template <class C> C* FindGameObject() {
		for (GameObject* obj : objects) {
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
				return inst;
		}
		return nullptr;
	}
	template <class C> std::list<C*> FindGameObjects() {
		std::list<C*> out;
		for (GameObject* obj : objects) {
			C* inst = dynamic_cast<C*>(obj);
			if (inst != nullptr)
				out.push_back(inst);
		}
		return out;
	}

private:
	ObjectManager(); // コンストラクターはprivateにする
	std::list<GameObject*> objects;
};
