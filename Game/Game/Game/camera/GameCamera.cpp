#include "stdafx.h"
#include "GameCamera.h"
#include"Player/Player.h"
GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	//�J����
	//m_target = m_player->GetPos();
	m_target.y += 50.0f;
	return true;
}

void GameCamera::Update()
{
	m_position = m_playerPos + m_toPos;
	//���_
	g_camera3D->SetTarget(m_target);
	//���W
	g_camera3D->SetPosition(m_position);
	//�J�����̍X�V�B
	g_camera3D->Update();
}