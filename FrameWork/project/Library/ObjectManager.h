#pragma once
//ObjectManager.h
// �ǂ�����ł��Ăׂ�N���X�̍���
// �@C�̊֐�
// �A�V���O���g��
// �Bnamespace�ň͂�
// �C�C���X�^���X���O���[�o���ɂ���
// ����̓V���O���g���ŏ���
#include <list>
class GameObject;

class ObjectManager {
public:
	static ObjectManager* GetInst() { // GetInst()��static�ɂ���
		static ObjectManager* instance = nullptr; // �N���X���Ɏ����̃C���X�^���X������
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
	/// obj��objects�ɒǉ�����
	/// </summary>
	/// <param name="obj"></param>
	void Push(GameObject* obj);

	/// <summary>
	/// objects����폜����
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
	ObjectManager(); // �R���X�g���N�^�[��private�ɂ���
	std::list<GameObject*> objects;
};
