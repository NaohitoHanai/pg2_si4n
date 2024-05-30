#include "Dragon.h"
#include "../Library/Time.h"
Dragon::Dragon()
{
	fires.clear();
	interval = 0;
	timer = 5.0f;
}

Dragon::~Dragon()
{
}

void Dragon::Update()
{
	if (timer > 0.0f) {
//		timer -= Time::DeltaTime();
		for (int i = 0; i < 2; i++) {
			Fire* fire = new Fire();
			fires.push_back(fire); // これが追加
		}
	}
	else {
		// 5秒たったので自分を消す
		if (fires.size()==0)
			DestroyMe();
	}

	// ToDo: fires全部のUpdateを呼ぶ
	for (auto itr = fires.begin(); itr != fires.end(); ) {
		Fire* f = *itr;
		f->Update();
		if (f->IsDead()) {
			delete f;
			itr = fires.erase(itr);
		}
		else {
			itr++;
		}
	}
}

void Dragon::Draw()
{
	// ToDo: fires全部のDrawを呼ぶ
	for (Fire* f : fires) {
		f->Draw();
	}
}

Dragon::Fire::Fire()
{
	position = VGet(0, 100, 0);
	//velocityに何かを設定する
	// rand()の値は0～RAND_MAXが出る。RAND_MAXは32767
	float dir = rand() * (2.0f * DX_PI_F) / RAND_MAX;
	float dirX = rand() * DegToRad(10.0f) / RAND_MAX;
	float height = rand() * 1.0f / RAND_MAX + 9.0f;
	velocity = VGet(0, height, 0) * MGetRotX(dirX)
		* MGetRotY(dir);
}

Dragon::Fire::~Fire()
{
}

void Dragon::Fire::Update()
{
	position += velocity;
	velocity.y -= 0.3f;
}

void Dragon::Fire::Draw()
{
	int b = rand() % 127;
//	DrawSphere3D(position, 2, 10, GetColor(255, 255, 128+b),
//		GetColor(255, 255, 128+b), TRUE);
	DrawLine3D(position, position + velocity*4, GetColor(255, 255, 128));
}

bool Dragon::Fire::IsDead()
{
	return (position.y <= 0.0f);
}
