#pragma once
#include "Object.h"
#include "Block.h"
class Board :
    public Object
{
public:
    Board();
    ~Board();
    void Update() override;
    void Render(HDC _hdc) override;

    void ClearFullLines();  // 가득 찬 줄을 지우는 함수
    bool CheckCollision(const std::vector<Block*>& blocks);

    void AddBlock(Block* block);  // 새로운 블록을 보드에 추가

    const int GetWidth() const { return boardWidth; }
    const int GetHeight() const { return boardHeight; }
    const int GetEndPos() const { return boardHeight; }
private:
    void CreateBlock(BLOCK_TYPE blockType);
private:
    int boardWidth;
    int boardHeight;

    Texture* m_pTex;

    Block* currentBlock;
    BLOCK_TYPE nextBlock;
    std::vector<std::vector<Object*>> board;  // 2D 보드 상태 저장
};