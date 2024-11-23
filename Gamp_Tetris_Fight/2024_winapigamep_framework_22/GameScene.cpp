#include "pch.h"
#include "GameScene.h"
#include "Block_I.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"
#include "Board.h"

void GameScene::Init()
{
	Object* obj = new Block_Z;
	obj->SetPos({ SCREEN_WIDTH / 2,
			SCREEN_HEIGHT /2});
	AddObject(obj, LAYER::BACKGROUND);
}

void GameScene::Update()
{
	Scene::Update();
}
