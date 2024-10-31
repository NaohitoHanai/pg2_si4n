#include "SaveLoad.h"
#include <fstream>
#include "Player.h"
#include "Coin.h"

void SaveLoad::Save()
{
	std::ofstream ofs("save.dat", std::ios::binary);

	std::list<Coin*> coins = FindGameObjects<Coin>();
	for (auto c : coins) {
		VECTOR cPos = c->Position();
		ofs.write((char*)&cPos, sizeof(cPos));
	}
	Player* p = FindGameObject<Player>();
	ofs.write((char*)&(p->Position()), sizeof(VECTOR));
	ofs.close();
}

void SaveLoad::Load()
{
	Player* p = FindGameObject<Player>();
	if (p != nullptr) {
		p->DestroyMe();
	}
	std::ifstream ifs("save.dat", std::ios::binary);
	VECTOR pos;
	ifs.read((char*)&pos, sizeof(pos));
	new Player(pos);
	ifs.close();
}
