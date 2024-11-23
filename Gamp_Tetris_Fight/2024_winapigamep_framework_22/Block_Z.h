#pragma once
#include "Block_Parent.h"
#include "Block.h"
class Block_Z :
    public Block_Parent
{
public:
    Block_Z();
    ~Block_Z();
    void Update() override;
    void Render(HDC _hdc) override;
    void Rotate();

    void MoveDown();

    // override
    bool CheckCollision(const std::vector<Vec2>& positions) override;
    bool GetBlocks(const std::vector<Block>& blockVec) override;
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

    bool isWaiting; // ���� ��� ��������
    bool isBuilt; // ���� �ٴڿ� �׿�����
    vector<Block*> blockVec;

    Vec2 position;
    Vec2 m_vDir;

    int rotationIndex; // ���� ȸ�� ���¸� ��Ÿ���� �ε���
    int Rotation[4][3][3] =
    {
        {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        },

        {
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}
        },

        {
            {0, 0, 0},
            {0, 1, 1},
            {1, 1, 0}
        },

        {
            {1, 0, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    };
};

