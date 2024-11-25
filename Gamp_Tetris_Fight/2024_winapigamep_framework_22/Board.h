#pragma once
#include "Object.h"
#include "Block_Parent.h"
#include "Block.h"
class Board :
    public Object
{public:
    Board();
    ~Board();

    void Update() override;
    void Render(HDC _hdc) override;

    void BuildBlock(Block_Parent* blockParent); // ��� ����
    void ClearFullRows(); // ���� �� �� ����
    bool IsRowFull(int row) const; // Ư�� ���� ���� á���� Ȯ��
    void RemoveRow(int row); // Ư�� �� ����
    void MoveBlocksDown(int row); // �� ����� �Ʒ��� �̵�
    
    void CreateBlock();
    bool CheckFloor(const std::vector<Block*>& blocks) const; // ������ �� ������ �浹
    void CheckClampRotat(Block_Parent* block); // �� ��
    bool CheckClampLeft(const std::vector<Block*>& blocks) const; // �翷 �浹
    bool CheckClampRight(const std::vector<Block*>& blocks) const; // �翷 �浹
    Vec2 GetBoardOrigin() const;
private:
    const int boardWidth = 10; // ���� ���� ũ��
    const int boardHeight = 20; // ���� ���� ũ��

    // Block Down
    int moveDownTimer = 0;
    const int moveDownInterval = 100;

    Texture* m_pTex;

    // 2D �迭�� ���� ���� ����
    Block* boardState[20][10] = { nullptr }; // nullptr: ��� ����, Block*: ��� ������
    vector<vector<Block*>> boardVec;

    Block_Parent* currentBlock = nullptr; // ���� �����̴� ���
    BLOCK_TYPE nextBlock; // ���� ���
};