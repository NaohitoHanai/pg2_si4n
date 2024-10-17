#include "Target.h"
#include "Bullet.h"

Target::Target()
{
	hModel = MV1LoadModel("data/target_001.mv1");
}

Target::Target(VECTOR pos)
{
	hModel = MV1LoadModel("data/target_001.mv1");
	position = pos;
}

Target::~Target()
{
}

void Target::Update()
{
	// ’e‚ª“–‚½‚Á‚½‚©”»’è‚·‚é
	Bullet* b = FindGameObject<Bullet>();
	if (b != nullptr) {
		auto ret = MV1CollCheck_Capsule(hModel, 0,
			b->Position(), b->OldPosition(), b->Radius);
		if (ret.HitNum > 0) {
			DestroyMe();
		}
	}
}

void Target::Draw()
{
	MV1SetPosition(hModel, position);
	MV1DrawModel(hModel);
}
