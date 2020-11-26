#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "camera/GameCamera.h"
#include "BackGround/BackGround.h"
#include "villagercharacter/Villager.h"
#include "Title/Title.h"
#include "Menu.h"
//FindGOについて
//FindGOは処理が重くなってしまうのでQueryGOsの内部でのみ使用しています。
//よって、Gameクラス内の他クラスのインスタンスを呼び出したいときは下記のようにしてください。
//Game* game = GetGame();
//Player* player = game->GetPlayer();
//インスタンスを生成したときは必要に応じてGet関数を追加してください。

//静的メンバ変数を定義する。
Game* Game::m_game = nullptr;

Game::Game()
{
	//インスタンスを一つだけにする。
	if (m_game == nullptr)
	{
		//インスタンスの登録。
		m_game = this;
	}
	else {
		//警告。
		abort();
	}
}

Game::~Game()
{
	m_game = nullptr;
}

void Game::OnDestroy() 
{
	//ゲームが消えるときに削除したい物はここに書いてね。
	DeleteGO(m_bg);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_villager);
	DeleteGO(m_menu);
	DeleteGO(this);
}

bool Game::Start()
{
	//生成一覧。
	m_bg = NewGO<BackGround>();
	m_gameCamera = NewGO<GameCamera>();
	m_player = NewGO<Player>();
	m_villager = NewGO<Villager>();
	return true;
}

void Game::Update()
{
	FlagUpdate();
	if (isGameDelete_flag)
	{
		DeleteGO(this);
	}
}

void Game::FlagUpdate()
{
	//Gameメニュー表示入力
	GameMenuFlag();
	//以降はフラグでメニュー画面での入力を簡易的に描いてます。
	switch (isGameMenu_flag)
	{
	case false:
		if (m_menu != nullptr) {
			DeleteGO(m_menu);
			isSpriteCreat_flag = true;
		}
		break;
	case true:
		//一度だけ呼びたいためフラグを使ってます。
		if (isSpriteCreat_flag) {
			m_menu = NewGO<Menu>();
			isSpriteCreat_flag = false;
		}
		//メニュー画面からセーブして終了すると思ったので下記のように書いてます。
		//どう森のことよくわからないので許してヒヤシンス。
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			Title* title = NewGO<Title>();
			isGameDelete_flag = true;
		}
		break;
	}
}

void Game::GameMenuFlag()
{
	if (g_pad[0]->IsTrigger(enButtonX) && !isGameMenu_flag)
	{
		isGameMenu_flag = true;
	}
	else if (g_pad[0]->IsTrigger(enButtonX) && isGameMenu_flag)
	{
		isGameMenu_flag = false;
	}
}