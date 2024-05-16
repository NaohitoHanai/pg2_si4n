#pragma once
#include "../Library/GameObject.h"

/// <summary>
/// �ԉΑS�̂̓����ƕ\��������
/// �R�t���[���ɂP�ΉԂ𐶐�����
/// �T�b�ŏI���
/// </summary>
class Dragon : public GameObject {
public:
	Dragon();
	~Dragon();
	void Update() override;
	void Draw() override;
private:
	/// <summary>
	/// �ΉԂP�̓����ƕ\��������
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
	std::list<Fire*> fires; // �|�C���^�[�̏ꍇ

	int interval; // 3�t���[���𐔂���
	float timer; // �T�b�𐔂���
};