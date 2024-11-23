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

    void ClearFullLines();  // ���� �� ���� ����� �Լ�
    bool CheckCollision(const std::vector<Block*>& blocks);

    void AddBlock(Block* block);  // ���ο� ����� ���忡 �߰�

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
    std::vector<std::vector<Object*>> board;  // 2D ���� ���� ����
};