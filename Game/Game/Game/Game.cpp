#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include"camera/GameCamera.h"
#include "BackGround/BackGround.h"

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
	if (m_player != nullptr)
	{
		DeleteGO(m_player);
	}
	if (m_gameCamera != nullptr)
	{
		DeleteGO(m_gameCamera);
	}
	if (m_bg != nullptr) {
		DeleteGO(m_bg);
	}
}

bool Game::Start()
{
	//生成一覧。
	m_player = NewGO<Player>();
	//BackGround* bg = NewGO<BackGround>();

	m_gameCamera = NewGO<GameCamera>();
	m_gameCamera->BindPlayer(m_player);
	return true;
}

void Game::Update()
{
}