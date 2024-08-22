#include "App.h"
#include "SceneManager.h"
#include <DxLib.h>

void AppInit()
{
	SceneManager::Init();
}

void AppUpdate()
{
	SceneManager::Update();
}

void AppDraw()
{
	SceneManager::Draw();
}

void AppRelease()
{
	SceneManager::Release();
}

bool AppIsExit()
{
	return SceneManager::IsExit();
}