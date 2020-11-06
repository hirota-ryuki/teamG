#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Start()
{
	m_player = NewGO<Player>(GOPrio_Defalut, "Player");
	return true;
}

void Game::Update()
{

}