#include "SaveLoad.h"
#include <fstream>
#include "Player.h"
#include "Coin.h"

struct Header {
	char chunk[4];
	int fileSize;
	int checkSum;
};

void SaveLoad::Save()
{
	std::ofstream ofs("save.dat", std::ios::binary);

	Header header;
	header.chunk[0] = 'S';
	header.chunk[1] = 'A';
	header.chunk[2] = 'V';
	header.chunk[3] = 'E';
	header.fileSize = 0;
	header.checkSum = 0;
	ofs.write((char*)&header, sizeof(header));

	fileSize = 0;
	checkSum = 0;

	std::list<Coin*> coins = FindGameObjects<Coin>();
	int size = coins.size();
	WriteData(ofs, (char*)&size, sizeof(size));
	for (auto c : coins) {
		VECTOR cPos = c->Position();
		WriteData(ofs, (char*)&cPos, sizeof(cPos));
	}
	Player* p = FindGameObject<Player>();
	WriteData(ofs, (char*)&(p->Position()), sizeof(VECTOR));

	ofs.seekp(4); // fileSizeの場所
	ofs.write((char*)&fileSize, sizeof(fileSize));
	ofs.seekp(8); // checkSumの場所
	ofs.write((char*)&checkSum, sizeof(checkSum));
	ofs.close();
}

void SaveLoad::Load()
{
	Player* p = FindGameObject<Player>();
	if (p != nullptr) {
		p->DestroyMe();
	}
	std::list<Coin*> coins = FindGameObjects<Coin>();
	for (Coin* c : coins) {
		c->DestroyMe();
	}

	std::ifstream ifs("save.dat", std::ios::binary);
	Header header;
	ifs.read((char*)&header, sizeof(header));

	// ファイルサイズを求める
	ifs.seekg(0, std::ios::_Seekend); // 一番最後
	fileSize = ifs.tellg(); // この場所が、先頭から何バイトめ 
	fileSize -= sizeof(header); // ヘッダーの分を減らす
	ifs.seekg(sizeof(header), std::ios::_Seekbeg);
									// 元の位置に戻す
	// チェックサムを計算する
	checkSum = 0;
	for (int i = 0; i < fileSize; i++) {
		unsigned char c;
		ifs.read((char*)&c, sizeof(c));
		checkSum += c;
	}
	// エラーチェック
	const char* check = "SAVE";
	for (int i = 0; i < 4; i++) {
		if (header.chunk[i] != check[i]) {
			MessageBox(0, "このゲームのデータではありません",
				"LOAD ERROR", MB_OK);
			return;
		}
	}
	if (header.fileSize != fileSize) {
		MessageBox(0, "ファイルが破損していました",
			"LOAD ERROR", MB_OK);
		return;
	}
	if (header.checkSum != checkSum) {
		MessageBox(0, "データを正しく読めませんでした",
			"LOAD ERROR", MB_OK);
		return;
	}

	ifs.seekg(sizeof(header), std::ios::_Seekbeg);
	int size;
	ifs.read((char*)&size, sizeof(size));

	VECTOR pos;
	for (int i = 0; i < size; i++) {
		ifs.read((char*)&pos, sizeof(pos));
		new Coin(pos);
	}

	ifs.read((char*)&pos, sizeof(pos));
	new Player(pos);
	ifs.close();
}

void SaveLoad::WriteData(std::ofstream& ofs, char* adr, int size)
{
	ofs.write(adr, size);
	fileSize += size;
	unsigned char* p = (unsigned char*)adr;
	for (int i = 0; i < size; i++) {
		checkSum += *p++;
	}
}














