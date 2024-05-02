#pragma once
//
// Goblin.h
//                   N.Hanai
//
#include "../Library/GameObject.h"
#include "GoblinAI.h"

/// <summary>
/// ゴブリンキャラ
/// </summary>
class Goblin : public GameObject
{
public:
	Goblin();
	~Goblin();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// プレイヤーからの攻撃を受ける
	/// 線分とモデルとを当てて、当たったら、プレイヤーの
	/// 反対側に飛ぶ
	/// </summary>
	/// <param name="playerPos">プレイヤーの位置</param>
	/// <param name="weaponLine1">攻撃線１</param>
	/// <param name="weaponLine2">攻撃線２</param>
	/// <returns>当たったらtrue</returns>
	bool PlayerAttack(VECTOR playerPos, VECTOR weaponLine1, VECTOR weaponLine2);

	VECTOR Position() {
		return position;
	}
	void AddPosition(const VECTOR& pos) {
		position += pos;
	}
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	GoblinAI* ai;
};