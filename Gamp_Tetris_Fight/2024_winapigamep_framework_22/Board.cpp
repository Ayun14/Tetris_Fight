#include "pch.h"
#include "Board.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"

#include "Block.h"
#include "Block_Parent.h"
#include "Texture.h"
#include "Scene.h"
#include "Block_I.h"
#include "Block_J.h"
#include "Block_L.h"
#include "Block_O.h"
#include "Block_S.h"
#include "Block_T.h"
#include "Block_Z.h"
#include <cstdlib>

Board::Board() :
    boardWidth(10), boardHeight(20),
    currentBlock(nullptr), nextBlock(BLOCK_TYPE::NONE)
{
    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Board", L"Texture\\gamp-background.bmp");
    boardVec.resize(boardHeight, std::vector<Block*>(boardWidth));
}

Board::~Board()
{
}

void Board::Render(HDC _hdc)
{
    Vec2 vPos = GetPos();
    Vec2 vSize = GetSize();
    int width = m_pTex->GetWidth();
    int height = m_pTex->GetHeight();
    ::TransparentBlt(_hdc
        , (int)(vPos.x - width / 2)
        , (int)(vPos.y - height / 2)
        , width, height,
        m_pTex->GetTexDC()
        , 0, 0, width, height, RGB(255, 0, 255));
}

void Board::Update()
{
#pragma region BlockMove
    if (currentBlock)
    {

        // 위쪽 화살표 키를 눌러 블록 회전
        if (GET_KEYDOWN(KEY_TYPE::UP))
        {
            currentBlock->Rotate();
            CheckClampRotat(currentBlock);
        }

        // 양옆 화살표 키를 눌러 블록 이동
        if (GET_KEYDOWN(KEY_TYPE::LEFT))
        {
            currentBlock->MoveSide(true);
            if (false == CheckClampLeft(currentBlock->GetBlocks()))
                currentBlock->MoveSide(false);
        }
        if (GET_KEYDOWN(KEY_TYPE::RIGHT))
        {
            currentBlock->MoveSide(false);
            if (false == CheckClampRight(currentBlock->GetBlocks()))
                currentBlock->MoveSide(true);
        }

        // Block Down
        if (moveDownTimer >= moveDownInterval)
        {
            currentBlock->MoveDown();
            moveDownTimer = 0;

            if (CheckFloor(currentBlock->GetBlocks()))
            {
                // 1. 블럭 쌓고
                BuildBlock(currentBlock);
                // 2. 새로운 블럭 생성
                currentBlock = nullptr;
                CreateBlock();
            }
        }
        else
            moveDownTimer++;
    }
#pragma endregion
}

void Board::BuildBlock(Block_Parent* blockParent)
{
    Vec2 boardOrigin = GetBoardOrigin();

    for (Block* block : blockParent->GetBlocks())
    {
        // 보드 기준으로 계산한 위치
        float x = block->GetPos().x - boardOrigin.x;
        float y = block->GetPos().y - boardOrigin.y;

        int row = y / BLOCK_SIZE;
        int col = x / BLOCK_SIZE;

        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth)
        {
            if (boardVec[row][col] == nullptr)
                boardVec[row][col] = block;
        }
    }
}

void Board::ClearFullRows() 
{
    for (int row = 0; row < boardHeight; ++row) 
    {
        if (IsRowFull(row)) 
        {
            RemoveRow(row);
            MoveBlocksDown(row);
        }
    }
}

bool Board::IsRowFull(int row) const 
{
    for (int col = 0; col < boardWidth; ++col) 
    {
        if (boardState[row][col] == nullptr) 
        {
            return false; // 빈 칸이 있으면 가득 차지 않음
        }
    }
    return true; // 모든 칸이 차 있음
}

void Board::RemoveRow(int row)
{
    for (int col = 0; col < boardWidth; ++col) 
    {
        delete boardState[row][col]; // 블록 객체 삭제
        boardState[row][col] = nullptr;
    }
}

void Board::MoveBlocksDown(int row) 
{
    for (int r = row; r > 0; --r) 
    {
        for (int col = 0; col < boardWidth; ++col) 
        {
            boardState[r][col] = boardState[r - 1][col];
            if (boardState[r][col]) 
            {
                Vec2 pos = boardState[r][col]->GetPos();
                pos.y += BLOCK_SIZE; // 한 칸 아래로 이동
                boardState[r][col]->SetPos(pos);
            }
        }
    }

    // 맨 윗줄 초기화
    for (int col = 0; col < boardWidth; ++col) 
        boardState[0][col] = nullptr;
}

#pragma region ClampCheck

bool Board::CheckFloor(const std::vector<Block*>& blocks) const
{
    Vec2 boardOrigin = GetBoardOrigin();
    float boardFloor = GetPos().y + GetSize().y / 2; // 보드의 시작점(Screen Space 기준)

    for (const Block* block : blocks)
    {
        if ((block->GetPos().y + BLOCK_SIZE / 2) == boardFloor)
            return true;

        // 보드 기준으로 계산한 위치
        float x = block->GetPos().x - boardOrigin.x;
        float y = block->GetPos().y - boardOrigin.y;

        int row = y / BLOCK_SIZE + 1; // 한칸 아래 검사
        int col = x / BLOCK_SIZE;

        if (row >= 0 && row < boardHeight && col >= 0 && col < boardWidth)
        {
            if (boardVec[row][col] != nullptr)
            {
                cout << "True" << endl;
                return true;
            }
        }
    }
    return false;
}

void Board::CheckClampRotat(Block_Parent* block)
{
    if (false == CheckClampLeft(block->GetBlocks()))
    {
        currentBlock->MoveSide(false);
    }
    if (false == CheckClampRight(block->GetBlocks()))
    {
        currentBlock->MoveSide(true);
    }
}

bool Board::CheckClampLeft(const std::vector<Block*>& blocks) const
{
    float boardLeftOrigin = GetBoardOrigin().x; // 보드의 시작점(Screen Space 기준)

    for (const Block* block : blocks)
    {
        float x = block->GetPos().x;
        if (x - BLOCK_SIZE / 2 < boardLeftOrigin)
            return false;
    }
    return true;
}

bool Board::CheckClampRight(const std::vector<Block*>& blocks) const
{
    float boardRightOrigin = GetBoardOrigin().x + boardWidth * BLOCK_SIZE;

    for (const Block* block : blocks)
    {
        float x = block->GetPos().x;
        if (x + BLOCK_SIZE / 2 > boardRightOrigin)
            return false;
    }
    return true;
}

#pragma endregion

// 완료
Vec2 Board::GetBoardOrigin() const
{
    return Vec2(
        (SCREEN_WIDTH - boardWidth * BLOCK_SIZE) / 2,  // 보드가 화면의 가운데 정렬된 경우
        (SCREEN_HEIGHT - boardHeight * BLOCK_SIZE) / 2
    );
}

// 완료
void Board::CreateBlock()
{
    if (nextBlock == BLOCK_TYPE::NONE)
        nextBlock = (BLOCK_TYPE)(rand() % 7);

    Block_Parent* block = nullptr;
    switch (nextBlock)
    {
    case BLOCK_TYPE::BLOCK_I:
        block = new Block_I;
        break;
    case BLOCK_TYPE::BLOCK_J:
        block = new Block_J;
        break;
    case BLOCK_TYPE::BLOCK_L:
        block = new Block_L;
        break;
    case BLOCK_TYPE::BLOCK_O:
        block = new Block_O;
        break;
    case BLOCK_TYPE::BLOCK_S:
        block = new Block_S;
        break;
    case BLOCK_TYPE::BLOCK_Z:
        block = new Block_Z;
        break;
    case BLOCK_TYPE::BLOCK_T:
        block = new Block_T;
        break;
    }

    // 보드의 시작점 좌표
    float boardStartY = GetPos().y - (boardHeight * BLOCK_SIZE) / 2;

    // 블록을 보드의 -1번째 줄에 배치
    float blockStartX = GetPos().x;
    float blockStartY = boardStartY + BLOCK_SIZE * 2;

    block->SetPos({ blockStartX - BLOCK_SIZE / 2, blockStartY - BLOCK_SIZE / 2 });
    currentBlock = block;
    GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);

    // 다음 블럭 지정
    nextBlock = (BLOCK_TYPE)(rand() % 7);

    block->SetBlockPosition();
}

//bool Board::CheckCollision(Block_Parent* blockParent)
//{
//    const auto& blocks = blockParent->GetBlocks();
//
//    float boardEndY = GetPos().y + (GetSize().y / 2); // 보드 아래 y값
//    for (Block* block : blocks) 
//    {
//        // 1. 바닥에 도착 했는가?
//        Vec2 pos = block->GetPos();
//        if (pos.y + (block->GetSize().y / 2) >= boardEndY)
//            return true;
//
//        // 2. 밑에 저장된 블럭이 있는가?
//        // 보드 기준으로 계산한 위치
//        float x = (SCREEN_WIDTH / 2) - (GetSize().x / 2);
//        float y = (SCREEN_HEIGHT / 2) - (GetSize().y / 2);
//        Vec2 newPos = { pos.x - x, pos.y - y };
//
//        // 검사할 위치
//        int row = ((newPos.x + (block->GetSize().x / 2)) / 20) + 1;
//        int col = ((newPos.y + (block->GetSize().y / 2)) / 20) + 1;
//        if (row >= 0 && row < boardWidth && col >= 0 && col < boardHeight)
//        {
//            if (board[row][col] != nullptr)
//                return true;
//        }
//    }
//
//    return false;
//}