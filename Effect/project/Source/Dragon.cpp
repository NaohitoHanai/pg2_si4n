#include "Dragon.h"

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
	if (++interval >= 3) {
		interval = 0;
		Fire* fire = new Fire();
		fires.push_back(fire); // ‚±‚ê‚ª’Ç‰Á
	}
	// ToDo: fires‘S•”‚ÌUpdate‚ğŒÄ‚Ô
	for (std::list<Fire*>::iterator itr = fires.begin(); itr != fires.end(); ) {
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
	// ToDo: fires‘S•”‚ÌDraw‚ğŒÄ‚Ô
	for (Fire* f : fires) {
		f->Draw();
	}
}

Dragon::Fire::Fire()
{
	position = VGet(0, 100, 0);
	//velocity‚É‰½‚©‚ğİ’è‚·‚é
	float dir = rand() * 2.0f * DX_PI_F / RAND_MAX;
	velocity = VGet(0, 10, 0) * MGetRotX(DegToRad(5.0))
		* MGetRotY(dir);
}

Dragon::Fire::~Fire()
{
}

void Dragon::Fire::Update()
{
	position += velocity;
	velocity.y -= 0.3f;
	if (position.y <= 0.0) {
	}
}

void Dragon::Fire::Draw()
{
	DrawSphere3D(position, 10, 10, GetColor(255, 128, 128),
		GetColor(255, 128, 128), TRUE);
}

bool Dragon::Fire::IsDead()
{
	return (position.y <= 0.0f);
}
