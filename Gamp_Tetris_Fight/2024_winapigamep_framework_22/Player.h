#pragma once
#include "Object.h"
#include "InputManager.h"

class Texture;

class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
	void SetKey(KEY_TYPE _leftKey, KEY_TYPE _rightKey) {
		m_leftMoveKey = _leftKey;
		m_rightMoveKey = _rightKey;
	}
protected:
	bool CanUseSkill();
	void UseSkill();
private:
	//void CreateProjectile();
	Texture* m_pTex;
protected:
	KEY_TYPE m_leftMoveKey;
	KEY_TYPE m_rightMoveKey;
};

