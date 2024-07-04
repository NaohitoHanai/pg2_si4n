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

struct SaveHeader {
	char chunk[4];
	int size;
	short version;
	unsigned short checkSum;
};

void writeData(std::vector<char>& dev, char* data, int size)
{
	for (int i = 0; i < size; i++) {
		dev.push_back(data[i]);
	}
}

void Savedata::Save()
{
	// �Z�[�u�f�[�^�̑O�ɂ���f�[�^
	// �`�����N�i�f�[�^�̎��ʎq�F�S�̕����R�[�h�j
	// �Z�[�u�f�[�^�̃T�C�Y
	// �`�F�b�N�T���i�f�[�^�����h�~�F�S�f�[�^�̍��v�l�j
	// �o�[�W�����ԍ�
	std::ofstream fs("save.dat", std::ios::binary);
	if (!fs) {
		// �G���[���b�Z�[�W��\���A������
	}
	std::vector<char> savedata;

	// �v���C���[�ƃS�u�����̍��W��ۑ�����
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	VECTOR pPos = pPlayer->Position();
//	fs.write((char*)&pPos, sizeof(VECTOR));
	writeData(savedata, (char*)&pPos, sizeof(VECTOR));

	std::list<Goblin*> goblins = ObjectManager::FindGameObjects<Goblin>();
	int size = goblins.size();
//	fs.write((char*)&size, sizeof(int));
	writeData(savedata, (char*)&size, sizeof(int));
	for (Goblin* g : goblins) {
		VECTOR gPos = g->Position();
//		fs.write((char*)&gPos, sizeof(VECTOR));
		writeData(savedata, (char*)&gPos, sizeof(VECTOR));
	}

	SaveHeader header;
	memcpy(header.chunk, "HANA", 4);
	header.version = 3;
	header.size = savedata.size();
	unsigned short sum = 0;
	for (char c : savedata) {
		sum += (unsigned char)c;
	}
	header.checkSum = sum;
	fs.write((char*)&header, sizeof(SaveHeader));
	fs.write(&savedata[0], savedata.size());
	savedata.clear();
	fs.close();
	MessageBox(nullptr, "�Z�[�u�f�[�^�̕ۑ��ɐ������܂���",
		"�Z�[�u", MB_OK);
}

void Savedata::Load()
{
	std::ifstream fs("save.dat", std::ios::binary);
	VECTOR pos;
	fs.read((char*)&pos, sizeof(VECTOR));
	Player* pl = Instantiate<Player>();
	pl->SetPosition(pos);
	int size;
	fs.read((char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		Goblin* g = Instantiate<Goblin>();
		fs.read((char*)&pos, sizeof(VECTOR));
		g->SetPosition(pos);
	}
	fs.close();
}
