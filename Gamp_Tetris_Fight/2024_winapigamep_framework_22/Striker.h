#pragma once
#include "Player.h"
class Striker : public Player
{
public:
	Striker();
	~Striker();
public:
	void Update() override;
protected:
	bool CanUseSkill();
	void UseSkill();
private:
	int m_skillCount = 0;
};

