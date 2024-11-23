#include "pch.h"
#include "Block_Z.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Collider.h"

Block_Z::Block_Z() :
	blockNum(4),
	isWaiting(false),
	isBuilt(false),
	position(1.f, 1.f),
	m_vDir(1.f, 1.f),
	rotationIndex(0)
{
	for (int i = 0; i < blockNum; ++i)
	{
		Block* block = new Block(texturePath);
		blockVec.push_back(block);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(block, LAYER::BLOCK);
	}

	SetBlockPosition();
}

Block_Z::~Block_Z()
{
}

void Block_Z::Update()
{
	if (isBuilt || isWaiting) return;

	// 'R' 키를 눌러 블록 회전
	if (GET_KEYDOWN(KEY_TYPE::R))
		Rotate();

	if (moveDownTimer >= moveDownInterval)
	{
		MoveDown();
		moveDownTimer = 0;
	}
	else
		moveDownTimer++;
}

void Block_Z::Render(HDC _hdc)
{
}

void Block_Z::Rotate()
{
	// 다음 회전 상태로 변경
	rotationIndex = (rotationIndex + 1) % 4;

	int centerIndex = 0;
	switch (rotationIndex)
	{
	case 0:
		centerIndex = 3;
		break;
	case 1:
		centerIndex = 1;
		break;
	case 2:
		centerIndex = 0;
		break;
	case 3:
		centerIndex = 2;
		break;
	}
	blockVec[centerIndex]->SetPos(position);
	Vec2 centerPos = blockVec[centerIndex]->GetPos();

	int index = 0;
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 3; ++x)
		{
			if (Rotation[rotationIndex][y][x] == 1)
			{
				Vec2 newPos = centerPos;
				newPos.x += (x - 1) * 20; // 블록 크기에 맞춰 조정
				newPos.y += (y - 1) * 20;
				blockVec[index++]->SetPos(newPos);
			}
		}
	}
}

void Block_Z::MoveDown()
{
	int centerIndex = 0;
	switch (rotationIndex)
	{
	case 0:
		centerIndex = 3;
		break;
	case 1:
		centerIndex = 1;
		break;
	case 2:
		centerIndex = 0;
		break;
	case 3:
		centerIndex = 2;
		break;
	}

	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		pos.y += 20; // 한 칸 아래로 이동
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) position = blockVec[i]->GetPos();
	}
}

bool Block_Z::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

bool Block_Z::GetBlocks(const std::vector<Block>& blockVec)
{
	return false;
}

void Block_Z::SetBlockPosition()
{
	// 현재 회전 상태에 따라 블록 위치 설정
	int index = 0;
	for (int row = 0; row < 3; ++row)
	{
		for (int col = 0; col < 3; ++col)
		{
			if (Rotation[rotationIndex][row][col] == 1)
			{
				if (index < blockVec.size())
				{
					blockVec[index]->SetPos({ SCREEN_WIDTH / 2 + col * 20, row * 20 });
					if (index == 3) position = blockVec[index]->GetPos();
					index++;
				}
			}
		}
	}
}

void Block_Z::EnterCollision(Collider* _other)
{
}

void Block_Z::StayCollision(Collider* _other)
{
}

void Block_Z::ExitCollision(Collider* _other)
{
}
