#pragma once

//StageObj.h
#include "../Library/GameObject.h"

class StageObj : public GameObject
{
public:
	StageObj();
	~StageObj();
	void Draw() override;
	void LoadModel(int kind);
	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	int Model() {
		return hModel;
	}
	int CModel() {
		return hCModel;
	}
private:
	int hModel;
	int hCModel; // “–‚½‚è”»’è‚Ìƒ‚ƒfƒ‹
	VECTOR position;
	VECTOR rotation;
	VECTOR scale;
};