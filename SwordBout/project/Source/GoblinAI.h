#pragma once
//GoblinAI.h
#include <list>
class Goblin;

class Node {
public:
	/// <summary>
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
	Node* parent; // �e�̃|�C���^�[
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