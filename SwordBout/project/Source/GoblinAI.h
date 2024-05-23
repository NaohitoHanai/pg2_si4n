#pragma once
//GoblinAI.h
#include <list>
#include "../Library/GameObject.h"
class Goblin;

class Node {
public:
	Node(GameObject* obj) {
		object = obj;
	}

	~Node();

	/// 	/// <summary>
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
	Node* parent; // 親のポインター(ToDo:これは使わない？）
	GameObject* object;
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
	GoblinAvoid(GameObject* obj) : Node(obj) {}
	bool NeedEnable() override;
	bool Update() override;
private:
	float timer;
};

class GoblinAttack : public Node {
public:
	GoblinAttack(GameObject* obj) : Node(obj) {}
	bool NeedEnable() override;
	bool Update() override;
private:
	float timer;
};

class Selector : public Node {
public:
	Selector(GameObject* obj);
	bool NeedEnable() override;
	bool Update() override;
protected:
	Node* selected;
};

class Sequencer : public Node {
public:
	Sequencer(GameObject* obj);
	bool NeedEnable() override;
	bool Update() override;
protected:
	std::list<Node*>::iterator itr;
};
