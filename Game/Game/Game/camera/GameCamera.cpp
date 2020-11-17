#include "stdafx.h"
#include "GameCamera.h"
#include"Player/Player.h"
#include"Game.h"
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	Game* game = Game::GetGame();
	m_player = game->GetPlayer();

	m_cameraState = toPlayer;
	return true;
}

void GameCamera::Update()
{
	StateCamera();
	//��ŏ������B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		isCameraTagChange_flag = true;
	}
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		isCameraTagChange_flag = false;
	}
}
//�J���������������B
void GameCamera::MoveCamera()
{
	const float m_targetUpY = 50.0f;
	//�J����
	m_target.y += m_targetUpY;
	m_position = m_player->GetPos() + m_toPos;
	m_target = m_player->GetPos();

	//���_
	g_camera3D->SetTarget(m_target);
	//���W
	g_camera3D->SetPosition(m_position);
	//�J�����̍X�V�B
	g_camera3D->Update();
}
//�J�����̓����Ȃ��Ƃ��̏����B
void GameCamera::StopCamera()
{
	//�w��̏ꏊ����́B
	m_position = m_position1;
	m_target = m_target1;

	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_position);
	g_camera3D->Update();
}
//�J�����̎��_�ύX
void GameCamera::ChangePointOfView()
{
	if (!isCameraTagChange_flag)
	{
		m_cameraState = toPlayer;
	}
	else if (isCameraTagChange_flag /*&& �w��ꏊ�̏��� */)
	{
		m_cameraState = toPosition1;
		/*//���Ԍo�߂�false��
		if (m_timer > m_limitTime)
		{
			m_cameraState = toPlayer;
			isCameraTagChange_flag = false;
		}*/
	}
	else if (isCameraTagChange_flag && !isCameraTagChange_flag/*&& �w��ꏊ�̏��� */)
	{
		m_cameraState = toPosition2;
		/*//���Ԍo�߂�false��
		if (m_timer > m_limitTime)
		{
			m_cameraState = toPlayer;
			isCameraTagChange_flag = false;
		}*/
	}
}
//��ԕω�
void GameCamera::StateCamera()
{
	switch (m_cameraState)
	{
	case GameCamera::toPlayer:
		ChangePointOfView();
		MoveCamera();
		break;
	case GameCamera::toPosition1:
		ChangePointOfView();
		StopCamera();
		break;
	case GameCamera::toPosition2:
		ChangePointOfView();
		StopCamera();
		break;
	}
}