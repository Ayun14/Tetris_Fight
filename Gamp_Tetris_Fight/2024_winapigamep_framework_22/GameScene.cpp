#include "pch.h"
#include "GameScene.h"
#include "Player.h"
#include "InputManager.h"

void GameScene::Init()
{
	/*for (size_t i = 0; i < 100; i++)
	{
		Object* obj = new Enemy;
		obj->SetPos({rand() % SCREEN_WIDTH,
				rand() % SCREEN_HEIGHT});
		obj->SetSize({100, 100});
		AddObject(obj, LAYER::ENEMY);
	}*/
	{
		Object* oPlayer1 = new Player;

		oPlayer1->SetPos({ SCREEN_WIDTH / 2.f,500.f });
		oPlayer1->SetSize({ 100.f,100.f });

		Player* pPlayer1 = static_cast<Player*>(oPlayer1);
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // 이동 방향 설정

		AddObject(oPlayer1, LAYER::PLAYER);
	}
	{
		Object* oPlayer2 = new Player;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 300.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // 이동 방향 설정

		AddObject(oPlayer2, LAYER::PLAYER);
	}
}
