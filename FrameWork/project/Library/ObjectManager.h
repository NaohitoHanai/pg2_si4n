#pragma once
//ObjectManager.h
// �ǂ�����ł��Ăׂ�N���X�̍���
// �@C�̊֐�
// �A�V���O���g��
// �Bnamespace�ň͂�
// �C�C���X�^���X���O���[�o���ɂ���
// ����̓V���O���g���ŏ���

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
private:
	ObjectManager(); // �R���X�g���N�^�[��private�ɂ���
};
