#include "pch.h"
#include "Board.h"
#include "ResourceManager.h"
#include "Block.h"
#include "Texture.h"
#include "SceneManager.h"
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
    boardWidth(8), boardHeight(15)
{
    m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Board", L"Texture\\Bullet.bmp");
    CreateBlock((BLOCK_TYPE)(rand() % 7));
    nextBlock = (BLOCK_TYPE)(rand() % 7);
}

Board::~Board()
{
}

void Board::Update()
{
    if (CheckCollision({ currentBlock }))
    {
        // 충돌이 발생하면 블록을 고정하고 새로운 블록을 생성
        AddBlock(currentBlock);
        CreateBlock(nextBlock);
        nextBlock = (BLOCK_TYPE)(rand() % 7);
    }

    ClearFullLines();  // 줄이 다 채워지면 그 줄을 지운다
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

void Board::ClearFullLines()
{
}

bool Board::CheckCollision(const std::vector<Block*>& blocks)
{
    return false;
}

void Board::AddBlock(Block* block)
{
}

void Board::CreateBlock(BLOCK_TYPE blockType)
{
    Object* block = nullptr;
    switch (blockType)
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

    Vec2 vPos = GetPos();
    vPos.y -= GetSize().y / 2.f;
    block->SetPos(vPos);

    GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);
}
