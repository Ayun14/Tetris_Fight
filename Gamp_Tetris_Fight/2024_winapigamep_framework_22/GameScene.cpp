#include "pch.h"
#include "GameScene.h"
#include "Block_I.h"

void GameScene::Init()
{
	for (size_t i = 0; i < 100; i++)
	{
		Object* obj = new Block_I;
		obj->SetPos({SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2});
		//obj->SetSize({100, 100});
		AddObject(obj, LAYER::BLOCK);
	}
}
