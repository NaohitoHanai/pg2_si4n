#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// 花火全体の動きと表示をする
/// ３フレームに１個火花を生成する
/// ５秒で終わり
/// </summary>
class Dragon : public GameObject {
public:
	Dragon();
	~Dragon();
	void Update() override;
	void Draw() override;
private:
	/// <summary>
	/// 火花１個の動きと表示をする
	/// </summary>
	class Fire {
	public:
		Fire();
		~Fire();
		void Update();
		void Draw();
		bool IsDead();
	private:
		VECTOR position;
		VECTOR velocity;

	};
	std::list<Fire*> fires; // ポインターの場合

	int interval; // 3フレームを数える
	float timer; // ５秒を数える
};