#pragma once
#include "Object2D.h"

/// <summary>
/// �Ֆʂ̊Ǘ��A�u����Ă���R�}�̏��������Ă���
/// </summary>
class Board : public Object2D {
public:
	Board();
	~Board();
	void Update();
	void Draw();

	/// <summary>
	/// �}�X�ɒu����Ă���R�}�̏��
	/// </summary>
	enum Face {
		NODISC = -1, // �����u���ĂȂ�
		BLACK = 0,   // ��
		WHITE,       // ��
		MAX
	};

	/// <summary>
	/// �}�E�X���W����A�}�X�̈ʒu����肷��
	/// �}�X�̈ʒu������ł��Ȃ��ꍇ�́A(-1,-1)��Ԃ�
	/// </summary>
	/// <param name="screen">�}�E�X���W�i�E�B���h�E���̍��W�j</param>
	/// <returns>�}�X�̈ʒu</returns>
	IVector2 GetCellPosition(IVector2 screen);

	/// <summary>
	/// ���̃}�X�ɒu���邩�m�F����
	/// </summary>
	/// <param name="pos">�}�X�̈ʒu</param>
	/// <param name="color">�u���\��̃R�}�̐F</param>
	/// <returns>�Ђ�����Ԃ����i�u���Ȃ��ꍇ��0�j</returns>
	int CheckPut(IVector2 pos, Face color);

	/// <summary>
	/// �}�X�ɃR�}��u��
	/// </summary>
	/// <param name="pos">�}�X�̈ʒu</param>
	/// <param name="color">�u���R�}�̐F</param>
	void Put(IVector2 pos, Face color);

	/// <summary>
	/// �w�肵���F�̃R�}�̐���Ԃ�
	/// </summary>
	/// <param name="color">�u���R�}�̐F</param>
	/// <returns>�����̃R�}�̐�</returns>
	int GetScore(Face color);

	/// <summary>
	/// �p�X���邩�𒲂ׂ�
	/// </summary>
	/// <param name="color">�u���R�}�̐F</param>
	/// <returns>�u����ꏊ���Ȃ����true</returns>
	bool IsPass(Face color);

	/// <summary>
	/// �J�[�\���i�Ԙg�j��\������
	/// </summary>
	/// <param name="pos">�J�[�\����\������}�X�̈ʒu</param>
	void DrawCursor(IVector2 pos) {
		cursor = pos;
	};

	/// <summary>
	/// �J�[�\���i�Ԙg�j������
	/// </summary>
	void CursorOff() {
		cursor = IVector2(-1, -1);
	}

	static const int WIDTH = 8;  // �Ֆʂ̕�
	static const int HEIGHT = 8; // �Ֆʂ̍���
private:
	Face cells[HEIGHT + 2][WIDTH + 2]; // �Ֆʏ��i�O���ɂP�]�v�Ɏ��j
	IVector2 cursor; // �J�[�\���̈ʒu
	IVector2 position; // �Ղ̈ʒu
};