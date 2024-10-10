#pragma once
// Tank.h
#include "../Library/GameObject.h"

class TankGun : public GameObject {
public:
	TankGun();
	~TankGun();
	void Update() override;
	void Draw() override;
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};

class TankTower : public GameObject {
public:
	TankTower();
	~TankTower();
	void Update() override;
	void Draw() override;
	const MATRIX& Matrix() const {
		return matrix;
	}
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;
};

class Tank : public GameObject {
public:
	Tank();
	~Tank();
	void Update() override;
	void Draw() override;
	const MATRIX& Matrix() const {
		return matrix;
	}
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
	MATRIX matrix;
};