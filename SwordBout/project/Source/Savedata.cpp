#include "Savedata.h"
#include <fstream>
#include "Player.h"
#include "Goblin.h"

Savedata::Savedata()
{
}

Savedata::~Savedata()
{
}

void Savedata::Save()
{
	// �Z�[�u�f�[�^�̑O�ɂ���f�[�^
	// �`�����N�i�f�[�^�̎��ʎq�F�S�̕����R�[�h�j
	// �Z�[�u�f�[�^�̃T�C�Y
	// �`�F�b�N�T���i�f�[�^�����h�~�F�S�f�[�^�̍��v�l�j
	// �o�[�W�����ԍ�
	std::ofstream fs("save.dat", std::ios::binary);
	// �v���C���[�ƃS�u�����̍��W��ۑ�����
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPlayer->Position();
	fs.write((char*)&pPos, sizeof(VECTOR));

	std::list<Goblin*> goblins = ObjectManager::FindGameObjects<Goblin>();
	int size = goblins.size();
	fs.write((char*)&size, sizeof(int));
	for (Goblin* g : goblins) {
		VECTOR gPos = g->Position();
		fs.write((char*)&gPos, sizeof(VECTOR));
	}
	fs.close();
}

void Savedata::Load()
{
	std::ifstream fs("save.dat", std::ios::binary);
	VECTOR pos;
	fs.read((char*)&pos, sizeof(VECTOR));
	fs.close();
}
