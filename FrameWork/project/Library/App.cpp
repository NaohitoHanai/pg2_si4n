#include "App.h"
#include "SceneManager.h"
#include <DxLib.h>
#include "ObjectManager.h"

void AppInit()
{
	SceneManager::Init();
	ObjectManager::GetInst()->Init();
}

void AppUpdate()
{
	SceneManager::Update();
	ObjectManager::GetInst()->Update();
}

void AppDraw()
{
	SceneManager::Draw();
	ObjectManager::GetInst()->Draw();
}

void AppRelease()
{
	SceneManager::Release();
	ObjectManager::GetInst()->Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}