#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include"camera/GameCamera.h"

Game::Game()
{
}

Game::~Game()
{
	//ゲームが消える時すべてを消滅させます。
	if (m_player != nullptr)
	{
		DeleteGO(m_player);
	}
	if (m_gameCamera != nullptr)
	{
		DeleteGO(m_gameCamera);
	}
}

bool Game::Start()
{
	//生成一覧
	m_player = NewGO<Player>(GOPrio_Defalut, "Player");
	m_gameCamera = NewGO<GameCamera>(GOPrio_Defalut, "GameCamera");
	m_gameCamera->BindPlayer(m_player);
	return true;
}

void Game::Update()
{
}