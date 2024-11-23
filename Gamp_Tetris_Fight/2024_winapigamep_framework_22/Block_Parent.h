#pragma once
#include "Object.h"
#include "Block.h"
class Block_Parent :
    public Object
{
public:
    Block_Parent();
    virtual ~Block_Parent();

    virtual void Update() override;
    virtual void Render(HDC _hdc) override;

    virtual bool CheckCollision(const std::vector<Vec2>& positions) abstract;
    virtual bool GetBlocks(const std::vector<Block>& blockVec) abstract;
};