#include "stdafx.h"
#include "Game.h"
#include "Player/Player.h"
#include "camera/GameCamera.h"
#include "BackGround/BackGround.h"
#include "villagercharacter/Villager.h"
#include "Title/Title.h"
#include "Menu.h"
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
	//�Q�[����������Ƃ��ɍ폜���������͂����ɏ����ĂˁB
	DeleteGO(m_bg);
	DeleteGO(m_gameCamera);
	DeleteGO(m_player);
	DeleteGO(m_villager);
	DeleteGO(m_menu);
	DeleteGO(this);
}

bool Game::Start()
{
	//�����ꗗ�B
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
	//Game���j���[�\������
	GameMenuFlag();
	//�ȍ~�̓t���O�Ń��j���[��ʂł̓��͂��ȈՓI�ɕ`���Ă܂��B
	switch (isGameMenu_flag)
	{
	case false:
		if (m_menu != nullptr) {
			DeleteGO(m_menu);
			isSpriteCreat_flag = true;
		}
		break;
	case true:
		//��x�����Ăт������߃t���O���g���Ă܂��B
		if (isSpriteCreat_flag) {
			m_menu = NewGO<Menu>();
			isSpriteCreat_flag = false;
		}
		//���j���[��ʂ���Z�[�u���ďI������Ǝv�����̂ŉ��L�̂悤�ɏ����Ă܂��B
		//�ǂ��X�̂��Ƃ悭�킩��Ȃ��̂ŋ����ăq���V���X�B
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