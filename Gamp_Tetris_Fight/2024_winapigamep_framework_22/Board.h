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

    void BuildBlock(Block_Parent* blockParent); // 블록 고정
    void ClearFullRows(); // 가득 찬 줄 삭제
    bool IsRowFull(int row) const; // 특정 줄이 가득 찼는지 확인
    void RemoveRow(int row); // 특정 줄 제거
    void MoveBlocksDown(int row); // 위 블록을 아래로 이동
    
    void CreateBlock();
    bool CheckFloor(const std::vector<Block*>& blocks) const; // 고정할 지 않할지 충돌
    void CheckClampRotat(Block_Parent* block); // 돌 때
    bool CheckClampLeft(const std::vector<Block*>& blocks) const; // 양옆 충돌
    bool CheckClampRight(const std::vector<Block*>& blocks) const; // 양옆 충돌
    Vec2 GetBoardOrigin() const;
private:
    const int boardWidth = 10; // 보드 가로 크기
    const int boardHeight = 20; // 보드 세로 크기

    // Block Down
    int moveDownTimer = 0;
    const int moveDownInterval = 100;

    Texture* m_pTex;

    // 2D 배열로 보드 상태 관리
    Block* boardState[20][10] = { nullptr }; // nullptr: 비어 있음, Block*: 블록 포인터
    vector<vector<Block*>> boardVec;

    Block_Parent* currentBlock = nullptr; // 현재 움직이는 블록
    BLOCK_TYPE nextBlock; // 다음 블록
};