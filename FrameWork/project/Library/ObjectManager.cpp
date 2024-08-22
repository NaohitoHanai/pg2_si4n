#include "ObjectManager.h"
#include "../Source/Player.h" // ��

GameObject* player; // ��

void ObjectManager::Init()
{
	player = new Player();
}

void ObjectManager::Update()
{
	player->Update();
}

void ObjectManager::Draw()
{
	player->Draw();
}

void ObjectManager::Release()
{
}

ObjectManager::ObjectManager()
{
}
