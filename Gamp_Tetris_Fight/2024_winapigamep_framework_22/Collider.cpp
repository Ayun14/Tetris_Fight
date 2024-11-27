#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "GDISelector.h"
#include "Camera.h"

UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_vSize(30.f, 30.f)
	, m_vLatePos(0.f, 0.f)
	, m_vOffsetPos(0.f, 0.f)
{
}

Collider::~Collider()
{
}

void Collider::LateUpdate()
{
	const Object* pOwner = GetOwner();
	Vec2 vPos = pOwner->GetPos();
	m_vLatePos = vPos + m_vOffsetPos;
}

void Collider::Render(HDC _hdc)
{
	//PEN_TYPE ePen = PEN_TYPE::GREEN;
	//if (m_showDebug)
	//	ePen = PEN_TYPE::RED;
	//GDISelector pen(_hdc, ePen);
	//GDISelector brush(_hdc, BRUSH_TYPE::HOLLOW);
	//Vec2 camerapos = GET_SINGLE(Camera)->GetCameraPos();

	//RECT_RENDER(_hdc, m_vLatePos.x - ((int)camerapos.x), m_vLatePos.y - ((int)camerapos.y),
	//	m_vSize.x, m_vSize.y);
}

void Collider::EnterCollision(Collider* _other)
{
	m_showDebug = true;
	//cout << "Enter" << endl;
	GetOwner()->EnterCollision(_other);
}

void Collider::StayCollision(Collider* _other)
{
	GetOwner()->StayCollision(_other);
}

void Collider::ExitCollision(Collider* _other)
{
	m_showDebug = false;
	//cout << "Exit" << endl;
	GetOwner()->ExitCollision(_other);
}
