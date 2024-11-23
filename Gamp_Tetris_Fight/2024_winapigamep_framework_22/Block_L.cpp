#include "pch.h"
#include "Block_L.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "Collider.h"

Block_L::Block_L() :
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

Block_L::~Block_L()
{
}

void Block_L::Update()
{
	if (isBuilt || isWaiting) return;

	// 'R' Ű�� ���� ��� ȸ��
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

void Block_L::Render(HDC _hdc)
{
}

void Block_L::Rotate()
{
	// ���� ȸ�� ���·� ����
	rotationIndex = (rotationIndex + 1) % 4;

	int centerIndex = rotationIndex == 1 || rotationIndex == 2 ? 1 : 2;
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
				newPos.x += (x - 1) * 20; // ��� ũ�⿡ ���� ����
				newPos.y += (y - 1) * 20;
				blockVec[index++]->SetPos(newPos);
			}
		}
	}
}

void Block_L::MoveDown()
{
	int centerIndex = rotationIndex == 1 || rotationIndex == 2 ? 1 : 2;
	for (int i = 0; i < blockNum; ++i)
	{
		Vec2 pos = blockVec[i]->GetPos();
		pos.y += 20; // �� ĭ �Ʒ��� �̵�
		blockVec[i]->SetPos(pos);

		if (i == centerIndex) position = blockVec[i]->GetPos();
	}
}

bool Block_L::CheckCollision(const std::vector<Vec2>& positions)
{
	return false;
}

void Block_L::SetBlockPosition()
{
	// ���� ȸ�� ���¿� ���� ��� ��ġ ����
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
					if (index == 2) position = blockVec[index]->GetPos();
					index++;
				}
			}
		}
	}
}

void Block_L::EnterCollision(Collider* _other)
{
}

void Block_L::StayCollision(Collider* _other)
{
}

void Block_L::ExitCollision(Collider* _other)
{
}
