#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include"camera/GameCamera.h"
#include "BackGround/BackGround.h"

//FindGO�ɂ���
//FindGO�͏������d���Ȃ��Ă��܂��̂�QueryGOs�̓����ł̂ݎg�p���Ă��܂��B
//����āAGame�N���X���̑��N���X�̃C���X�^���X���Ăяo�������Ƃ��͉��L�̂悤�ɂ��Ă��������B
//Game* game = GetGame();
//Player* player = game->GetPlayer();
//�C���X�^���X�𐶐������Ƃ��͕K�v�ɉ�����Get�֐���ǉ����Ă��������B

//�ÓI�����o�ϐ����`����B
Game* Game::m_game = nullptr;

Game::Game()
{
	//�C���X�^���X��������ɂ���B
	if (m_game == nullptr)
	{
		//�C���X�^���X�̓o�^�B
		m_game = this;
	}
	else {
		//�x���B
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
	//�����ꗗ�B
	m_player = NewGO<Player>();
	//BackGround* bg = NewGO<BackGround>();

	m_gameCamera = NewGO<GameCamera>();
	m_gameCamera->BindPlayer(m_player);
	return true;
}

void Game::Update()
{
}