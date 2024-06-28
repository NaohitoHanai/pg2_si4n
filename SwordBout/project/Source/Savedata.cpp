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
	// セーブデータの前につけるデータ
	// チャンク（データの識別子：４つの文字コード）
	// セーブデータのサイズ
	// チェックサム（データ改造防止：全データの合計値）
	// バージョン番号
	std::ofstream fs("save.dat", std::ios::binary);
	// プレイヤーとゴブリンの座標を保存する
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
