#include "pch.h"
#include "Block_I.h"
#include "SceneManager.h"
#include "Scene.h"

Block_I::Block_I() :
	m_vDir(1.f, 1.f),
	isBuilt(false),
	blockNum(3)
{
	for (int i = 0; i < blockNum; ++i)
	{
		Block* block = new Block(texturePath);
		blockVec.push_back(block);
		block->SetPos({ SCREEN_WIDTH / 2, 20 * i }); // 여기서 위치 조절해주면 됨
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);
	}
}

Block_I::~Block_I() {}

void Block_I::Update()
{
}

void Block_I::Render(HDC _hdc)
{
}

void Block_I::EnterCollision(Collider* _other)
{
}

void Block_I::StayCollision(Collider* _other)
{
}

void Block_I::ExitCollision(Collider* _other)
{
}
