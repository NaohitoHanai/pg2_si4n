#pragma once
#include "../Library/GameObject.h"
#include <fstream>

class SaveLoad {
public:
	void Save();
	void Load();
private:
	int fileSize;
	int checkSum;
	void WriteData(std::ofstream& ofs, 
						char* adr, int size);
};
