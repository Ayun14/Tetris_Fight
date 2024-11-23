#pragma once
#include "Object.h"
#include "Block.h"
class Block_J :
    public Object
{
public:
    Block_J();
    ~Block_J(); 
    void Update() override;
    void Render(HDC _hdc) override;
    void Rotate();

    void MoveDown();
    bool CheckCollision(const std::vector<Vec2>& positions);
private:
    void SetBlockPosition();
public:
    void SetDir(Vec2 _dir)
    {
        m_vDir = _dir;
        m_vDir.Normalize();
    }
public:
    virtual void EnterCollision(Collider* _other);
    virtual void StayCollision(Collider* _other);
    virtual void ExitCollision(Collider* _other);
private:
    // Block Spawn
    int blockNum;
    wstring texturePath = L"Texture\\Bullet.bmp";

    // Block Down
    int moveDownTimer = 0;
    const int moveDownInterval = 1000;

    bool isWaiting; // 블럭이 대기 상태인지
    bool isBuilt; // 블럭이 바닥에 쌓였는지
    vector<Block*> blockVec;

    Vec2 position;
    Vec2 m_vDir;

    int rotationIndex; // 현재 회전 상태를 나타내는 인덱스
    int Rotation[4][3][3] =
    {
        {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        },

        {
            {0, 1, 1},
            {0, 1, 0},
            {0, 1, 0}
        },

        {
            {0, 0, 0},
            {1, 1, 1},
            {0, 0, 1}
        },

        {
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 0}
        }
    };
};


