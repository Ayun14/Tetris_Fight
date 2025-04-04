#pragma once
#include "pch.h"
#include "Component.h"
class Component;

class CameraComponent : public Component
{
public:
	CameraComponent();
	~CameraComponent();
public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
public:
	void ShakeCamera();
private:
	Vec2* m_pPos;
	float time;
};

