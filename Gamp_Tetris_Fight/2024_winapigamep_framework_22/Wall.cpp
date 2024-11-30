#include "pch.h"
#include "Wall.h"
#include "Collider.h"

Wall::Wall()
{
	this->AddComponent<Collider>();
}

Wall::~Wall()
{
}

void Wall::Update()
{
}

void Wall::Render(HDC _hdc)
{	
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y, vSize.x, vSize.y);
}
