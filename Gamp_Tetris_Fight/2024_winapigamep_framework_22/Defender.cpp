#include "pch.h"
#include "Defender.h"
#include "InputManager.h"

bool Defender::CanUseSkill() // �е��� ������ ������
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

	if (GET_KEYDOWN(KEY_TYPE::SPACE)) { // ����
		cout << "defender jump" << endl;
	}
	if (GET_KEYDOWN(KEY_TYPE::UP)) { // �е�
		UseSkill();
	}
}
