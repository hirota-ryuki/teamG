#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include"camera/GameCamera.h"
#include"BackGround/BackGround.h"

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
	if (m_bg != nullptr) {
		DeleteGO(m_bg);
	}
}

bool Game::Start()
{
	//生成一覧
	m_player = NewGO<Player>();
	m_gameCamera = NewGO<GameCamera>();
	m_bg = NewGO<BackGround>();
	m_gameCamera->BindPlayer(m_player);
	return true;
}

void Game::Update()
{
}