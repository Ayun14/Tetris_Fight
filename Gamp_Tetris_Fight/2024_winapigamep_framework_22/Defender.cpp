#include "pch.h"
#include "Defender.h"
#include "InputManager.h"

bool Defender::CanUseSkill() // 패딩은 언제가 가능함
{
	return true;
}

void Defender::UseSkill()
{
	if (CanUseSkill()) {
		cout << "defender use skill" << endl;
	}
}
void Defender::Update() {
	Player::Update();

	if (GET_KEYDOWN(KEY_TYPE::SPACE)) { // 점프
		cout << "defender jump" << endl;
	}
	if (GET_KEYDOWN(KEY_TYPE::UP)) { // 패딩
		UseSkill();
	}
}
