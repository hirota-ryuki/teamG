#include "stdafx.h"
#include "GameCamera.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	return true;
}

void GameCamera::Update()
{
	//カメラ
	Vector3 m_toPos = { 0.0f, 100.0f, 300.0f };
	Vector3 m_target = m_playerPos;
	m_target.y += 50.0f;
	Vector3 m_pos = m_playerPos + m_toPos;
	//視点
	g_camera3D->SetTarget(m_target);
	//座標
	g_camera3D->SetPosition(m_position);
	//カメラの更新。
	g_camera3D->Update();
}