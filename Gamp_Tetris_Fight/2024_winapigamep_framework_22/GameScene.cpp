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
	Board* board = new Board;
	board->SetPos({ SCREEN_WIDTH / 2,
			SCREEN_HEIGHT /2});
	board->SetSize({ 400.f, 800.f });
	AddObject(board, LAYER::BACKGROUND);
	board->CreateBlock();
}

void GameScene::Update()
{
	Scene::Update();
}
