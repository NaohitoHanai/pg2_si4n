#pragma once

/// <summary>
/// �V�[�����ς���Ă��A�ϐ���ێ����邽�߂̃N���X
/// Player��User�ɂ��邩�ACom�ɂ��邩��ێ����Ă���
/// �V���O���g���ō���Ă��܂�
/// </summary>
class DataCarrier {
private:
	DataCarrier();
	~DataCarrier();
public:
	static DataCarrier* GetInstance() {
		static DataCarrier inst;
		return &inst;
	}

	/// <summary>
	/// ���ꂼ��̐F��User�ɂ��邩�ACom�ɂ��邩
	/// </summary>
	/// <param name="id">�F�ԍ�(0:���A1:��)</param>
	/// <param name="user">user�̏ꍇtrue</param>
	void SetPlayUser(int id, bool user);

	/// <summary>
	/// User��Com����Ԃ�
	/// </summary>
	/// <param name="id">�F�ԍ�(0:���A1:��)</param>
	/// <returns>user�̏ꍇ��true</returns>
	bool IsPlayUser(int id) const;
private:
	bool player[2];
};