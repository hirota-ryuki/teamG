#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "camera/GameCamera.h"
#include "BackGround/BackGround.h"
#include"villagercharacter/Villager.h"

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
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		m_menu = NewGO<SpriteRender>(GOPrio_Sprite);
		m_menu->Init("Assets/sprite/KARI.dds", FRAME_BUFFER_W, FRAME_BUFFER_H);
	}
}