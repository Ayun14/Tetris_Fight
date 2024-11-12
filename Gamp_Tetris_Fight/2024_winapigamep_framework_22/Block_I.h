#pragma once
#include "Object.h"
#include "Block.h"
class Block_I :
    public Object
{
public:
	Block_I();
	~Block_I();
	void Update() override;
	void Render(HDC _hdc) override;
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
    wstring texturePath = L"Texture\\¾îÂ¼±¸.bmp";

	bool isBuilt; // ºí·°ÀÌ ¹Ù´Ú¿¡ ½×¿´´ÂÁö Ã¼Å©
	vector<Block> blockVec;

	Vec2 m_vDir;

    const int Rotation[4][3][3] =
    {
        {
            {0, 2, 0},
            {0, 2, 0},
            {0, 2, 0},
        },
        {
            {0, 0, 0},
            {2, 2, 2},
            {0, 0, 0},
        },
        {
            {0, 2, 0},
            {0, 2, 0},
            {0, 2, 0},
        },
        {
            {0, 0, 0},
            {2, 2, 2},
            {0, 0, 0},
        },
    };
};


