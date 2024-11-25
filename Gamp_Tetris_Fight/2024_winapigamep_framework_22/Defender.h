#pragma once
#include "Player.h"
class Defender : public Player
{
public:
	void Update() override;
protected:
	bool CanUseSkill();
	void UseSkill();
};

