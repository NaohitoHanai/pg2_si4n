#pragma once
//ObjectManager.h
// どこからでも呼べるクラスの作り方
// ①Cの関数
// ②シングルトン
// ③namespaceで囲む
// ④インスタンスをグローバルにする
// 今回はシングルトンで書く

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
private:
	ObjectManager(); // コンストラクターはprivateにする
};
