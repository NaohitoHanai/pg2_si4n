#pragma once
#include "../Library/GameObject.h"

class Ground : public GameObject
{
public:
	Ground();
	~Ground();
	void Draw() override;

	/// <summary>
	/// pos��XZ�n�_�̒n�ʂ̍��������߂�
	/// </summary>
	/// <param name="pos">���ׂ���W</param>
	/// <returns>�n�ʂ̍����i�n�ʂ��Ȃ�������-10000��Ԃ��j</returns>
	float GetHeight(VECTOR pos);
private:
	int hModel;
};