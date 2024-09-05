#pragma once
//ObjectManager.h
// どこからでも呼べるクラスの作り方
// ①Cの関数
// ②シングルトン
// ③namespaceで囲む
// ④インスタンスをグローバルにする
// 今回はシングルトンで書く
#include <list>
#include "GameObject.h"

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

private:
	ObjectManager(); // コンストラクターはprivateにする
	std::list<GameObject*> objects;
};
