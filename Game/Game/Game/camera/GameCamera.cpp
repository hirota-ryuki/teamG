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
	//カメラ
	//m_target = m_player->GetPos();
	m_target.y += 50.0f;
	return true;
}

void GameCamera::Update()
{
	m_position = m_playerPos + m_toPos;
	//視点
	g_camera3D->SetTarget(m_target);
	//座標
	g_camera3D->SetPosition(m_position);
	//カメラの更新。
	g_camera3D->Update();
}