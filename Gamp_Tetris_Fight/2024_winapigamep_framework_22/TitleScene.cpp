#include "pch.h"
#include "TitleScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
//#include "Enemy.h"
//#include "CollisionManager.h"
//#include "ResourceManager.h"

#include "Striker.h"
#include "Defender.h"

void TitleScene::Init()
{
	{
		Object* oPlayer1 = new Striker;

		oPlayer1->SetPos({ SCREEN_WIDTH / 2.f,300.f });
		oPlayer1->SetSize({ 100.f,100.f });

		Player* pPlayer1 = dynamic_cast<Player*>(oPlayer1);
		pPlayer1->SetKey(KEY_TYPE::A, KEY_TYPE::D); // 이동 방향 설정

		AddObject(oPlayer1, LAYER::PLAYER); // 레이어도 바꿔야할겅ㅁ
		//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	}
	{
		Object* oPlayer2 = new Defender;
		oPlayer2->SetPos({ SCREEN_WIDTH / 2.f, 500.f });
		oPlayer2->SetSize({ 100.f,100.f });

		Player* pPlayer2 = static_cast<Player*>(oPlayer2);
		pPlayer2->SetKey(KEY_TYPE::LEFT, KEY_TYPE::RIGHT); // 이동 방향 설정

		AddObject(oPlayer2, LAYER::PLAYER);// 레이어도 바꿔야할겅ㅁ
		//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	}

	/*Object* pObj = new Enemy;
	pObj->SetPos({ SCREEN_WIDTH / 2.f,150.f });
	pObj->SetSize({ 100.f,100.f });
	pObj->SetName(L"Enemy");
	AddObject(pObj, LAYER::ENEMY);

	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);

	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");*/
}

void TitleScene::Update()
{
	Scene::Update();
	/*if (GET_KEYDOWN(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");*/
}
