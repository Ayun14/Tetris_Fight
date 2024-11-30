#include "pch.h"
#include "GameScene.h"
//#include "Block_I.h"
//#include "Block_J.h"
//#include "Block_L.h"
//#include "Block_O.h"
//#include "Block_S.h"
//#include "Block_T.h"
//#include "Block_Z.h"
#include "Board.h"

#include "Wall.h"
#include "CollisionManager.h"

void GameScene::Init()
{
	
	{
		Board* board = new Board;
		board->SetPos({ SCREEN_WIDTH / 2 + 100,
				SCREEN_HEIGHT / 2});
		board->SetSize({ 400.f, 800.f });
		AddObject(board, LAYER::BACKGROUND);
		board->CreateBlock();

		m_boardPos = board->GetPos();
		m_boardSize = board->GetSize();
	}
    {
        float leftEdge = m_boardPos.x - m_boardSize.x / 2;
        float rightEdge = m_boardPos.x + m_boardSize.x / 2;
        float bottomEdge = m_boardPos.y + m_boardSize.y / 2;

        // Left Wall
        Wall* leftWall = new Wall;
        leftWall->SetPos({ leftEdge - 125, m_boardPos.y });
        leftWall->SetSize({ 50, (int)m_boardSize.y });
        AddObject(leftWall, LAYER::Wall);

        // Right Wall
        Wall* rightWall = new Wall;
        rightWall->SetPos({ rightEdge + -75, m_boardPos.y });
        rightWall->SetSize({ 50, (int)m_boardSize.y });
        AddObject(rightWall, LAYER::Wall);

        // Bottom Wall
        Wall* bottomWall = new Wall;
        bottomWall->SetPos({ m_boardPos.x - 100, bottomEdge + 25 });
        bottomWall->SetSize({ (int)m_boardSize.x, 50 });
        AddObject(bottomWall, LAYER::Wall);

        // Collision Layer ¼³Á¤
        GET_SINGLE(CollisionManager)->CheckLayer(LAYER::Wall, LAYER::PLAYER);
    }
}

void GameScene::Update()
{
	Scene::Update();
}
