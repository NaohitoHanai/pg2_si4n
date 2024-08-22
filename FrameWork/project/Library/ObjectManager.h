#pragma once
//ObjectManager.h
// どこからでも呼べるクラスの作り方
// �@Cの関数
// �Aシングルトン
// �Bnamespaceで囲む
// �Cインスタンスをグローバルにする
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
