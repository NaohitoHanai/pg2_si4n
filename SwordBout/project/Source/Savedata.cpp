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

void readData(char*& p, char* data, int size)
{
	for (int i = 0; i < size; i++) {
		data[i] = *p++;
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

	// �����ňÍ���
	for (auto& c : savedata) {
		c = c + 1;
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
	SaveHeader header;
	fs.read((char*)&header, sizeof(SaveHeader));
	if (strncmp(header.chunk, "HANA", 4) != 0) {
		MessageBox(nullptr, "���̃Q�[���̃f�[�^�ł͂���܂���",
			"�G���[", MB_OK);
		fs.close();
		return;
	}
	fs.seekg(0, std::ios_base::_Seekend); // ��ԍŌ�ɂ���
	int filesize = fs.tellg(); // �t�@�C���̃T�C�Y
	if (filesize != sizeof(header) + header.size) {
		//ToDo filesize��header.size�ƍ����Ă��邩�A�����ĂȂ���΃G���[�I��
		MessageBox(nullptr, "�f�[�^���j�����Ă��܂���",
			"�G���[", MB_OK);
		fs.close();
		return;
	}
	fs.seekg(sizeof(header), std::ios_base::_Seekbeg);
	unsigned short sum = 0;
	for (int i = 0; i < header.size; i++) {
		unsigned char c;
		fs.read((char*)&c, sizeof(char));
		sum += c;
	}
	if (sum != header.checkSum) {
		//ToDo checkSum��sum�������Ă��邩�A�����ĂȂ���΃G���[�I��
		MessageBox(nullptr, "�f�[�^���j�����Ă��܂�",
			"�G���[", MB_OK);
		fs.close();
		return;
	}

	// �{���̓o�[�W�������Ƃɕς���
	fs.seekg(sizeof(header), std::ios_base::_Seekbeg);
	char* buf = new char[header.size];
	fs.read(buf, header.size);

	for (int i = 0; i < header.checkSum; i++) {
		buf[i] -= 1;
	}

	char* readp = buf;
	VECTOR pos;
//	fs.read((char*)&pos, sizeof(VECTOR));
	readData(readp, (char*)&pos, sizeof(VECTOR));
	Player* pl = Instantiate<Player>();
	pl->SetPosition(pos);
	int size;
//	fs.read((char*)&size, sizeof(int));
	readData(readp, (char*)&size, sizeof(int));
	for (int i = 0; i < size; i++) {
		Goblin* g = Instantiate<Goblin>();
//		fs.read((char*)&pos, sizeof(VECTOR));
		readData(readp, (char*)&pos, sizeof(VECTOR));
		g->SetPosition(pos);
	}
	fs.close();
}
