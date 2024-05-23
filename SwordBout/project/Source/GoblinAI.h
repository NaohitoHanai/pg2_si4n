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
	/// ���܂����H
	/// </summary>
	/// <returns>�������̏ꍇ��true</returns>
	virtual bool NeedEnable();

	/// <summary>
	/// ���s����
	/// </summary>
	/// <returns>�������I�������true</returns>
	virtual bool Update();
protected:
	std::list<Node*> children; // �����̉��̎q
	Node* parent; // �e�̃|�C���^�[(ToDo:����͎g��Ȃ��H�j
	GameObject* object;
};

class GoblinAI {
public:
	GoblinAI(Goblin* p);
	~GoblinAI();
	void Update();
private:
	Goblin* parent; // �e�̃|�C���^�[��ۑ�����
	Node* rootNode; // �擪�̃m�[�h
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
