#include "pch.h"
#include "Block.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"

Block::Block() :
	m_vDir(1.f, 1.f),
	m_pTex(nullptr)
{
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Bullet.bmp");
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f,20.f });
}

Block::~Block() {}

void Block::Update()
{
	
}

void Block::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void Block::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"위에 있는 상대")
	{
		// 상대에게 데미지
	}
}

void Block::StayCollision(Collider* _other)
{
}

void Block::ExitCollision(Collider* _other)
{
}
