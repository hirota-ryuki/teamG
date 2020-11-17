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
	//後で消えるよ。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		isCameraTagChange_flag = true;
	}
	else if (g_pad[0]->IsTrigger(enButtonB))
	{
		isCameraTagChange_flag = false;
	}
}
//カメラが動く処理。
void GameCamera::MoveCamera()
{
	const float m_targetUpY = 50.0f;
	//カメラ
	m_target.y += m_targetUpY;
	m_position = m_player->GetPos() + m_toPos;
	m_target = m_player->GetPos();

	//視点
	g_camera3D->SetTarget(m_target);
	//座標
	g_camera3D->SetPosition(m_position);
	//カメラの更新。
	g_camera3D->Update();
}
//カメラの動かないときの処理。
void GameCamera::StopCamera()
{
	//指定の場所を入力。
	m_position = m_position1;
	m_target = m_target1;

	g_camera3D->SetTarget(m_target);
	g_camera3D->SetPosition(m_position);
	g_camera3D->Update();
}
//カメラの視点変更
void GameCamera::ChangePointOfView()
{
	if (!isCameraTagChange_flag)
	{
		m_cameraState = toPlayer;
	}
	else if (isCameraTagChange_flag /*&& 指定場所の条件 */)
	{
		m_cameraState = toPosition1;
		/*//時間経過でfalseに
		if (m_timer > m_limitTime)
		{
			m_cameraState = toPlayer;
			isCameraTagChange_flag = false;
		}*/
	}
	else if (isCameraTagChange_flag && !isCameraTagChange_flag/*&& 指定場所の条件 */)
	{
		m_cameraState = toPosition2;
		/*//時間経過でfalseに
		if (m_timer > m_limitTime)
		{
			m_cameraState = toPlayer;
			isCameraTagChange_flag = false;
		}*/
	}
}
//状態変化
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