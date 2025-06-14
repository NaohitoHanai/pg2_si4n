#pragma once
#include "Object2D.h"
#include "Board.h"

/// <summary>
/// �v���C���[�̏������s��
/// </summary>
class Player : public Object2D {
public:
	Player(Board::Face color);
	virtual ~Player();
	void Update() override;
	void Draw() override;

	/// <summary>
	/// �����̃^�[���ɂȂ���
	/// </summary>
	void TurnStart();

	/// <summary>
	/// �����̃^�[�����I����������Ԃ�
	/// </summary>
	/// <returns>�^�[���I��������true</returns>
	bool TurnEnd();

	/// <summary>
	/// �����̃R�}���u���邩�𒲂ׂ�
	/// </summary>
	/// <returns>�u����ꍇ��true</returns>
	bool CanPut();
private:

	/// <summary>
	/// �����̃^�[���̏���������
	/// �}�E�X���͂����āA�}�X��I������
	/// Com�v���C���[�́A�������p�����āAAI�Ń}�X��I������
	/// </summary>
	/// <returns>�I�������}�X</returns>
	virtual IVector2 SelectCell();
protected:
	Board::Face myColor; // �����̐F
private:
	enum State {
		WAIT = 0, // �v���C�҂�
		SELECT,   // �I��
	};
	State state;

	bool canPut; // �����̃R�}���u����ꍇ�Ɂu�u���܂���v��\�����邽��
};