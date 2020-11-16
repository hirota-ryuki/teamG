#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include"camera/GameCamera.h"
#include "BackGround/BackGround.h"

Game::Game()
{

}

Game::~Game()
{
	
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
	//ê∂ê¨àÍóóÅB
	m_player = NewGO<Player>();
	BackGround* bg = NewGO<BackGround>();

	m_gameCamera = NewGO<GameCamera>();
	m_gameCamera->BindPlayer(m_player);
	return true;
}

void Game::Update()
{
}