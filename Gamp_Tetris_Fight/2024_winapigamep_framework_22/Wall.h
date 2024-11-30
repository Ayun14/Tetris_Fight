#pragma once
#include "Object.h"

class Wall : public Object
{
public:
	Wall();
	~Wall();
public:
	void Update() override;
	void Render(HDC _hdc) override;
};

