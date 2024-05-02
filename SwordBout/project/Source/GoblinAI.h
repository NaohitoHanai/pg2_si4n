#pragma once
//GoblinAI.h
#include <list>
class Goblin;

class Node {
public:
	/// <summary>
	/// やりますか？
	/// </summary>
	/// <returns>やる条件の場合はtrue</returns>
	virtual bool NeedEnable();

	/// <summary>
	/// 実行する
	/// </summary>
	/// <returns>処理が終わったらtrue</returns>
	virtual bool Update();
protected:
	std::list<Node*> children; // 自分の下の子
	Node* parent; // 親のポインター
};

class GoblinAI {
public:
	GoblinAI(Goblin* p);
	~GoblinAI();
	void Update();
private:
	Goblin* parent; // 親のポインターを保存する
	Node* rootNode; // 先頭のノード
};

class GoblinAvoid : public Node {
public:
	bool NeedEnable() override;
	bool Update() override;
};

class GoblinAttack : public Node {
public:
	bool NeedEnable() override;
	bool Update() override;
};

class Selector : public Node {
public:
	Selector();
	bool NeedEnable() override;
	bool Update() override;
protected:
	Node* selected;
};