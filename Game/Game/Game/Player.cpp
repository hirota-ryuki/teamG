#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//プレイヤーを生成するモデルとシェーダーの情報。
	playerInitData.m_tkmFilePath = "Assets/modelData/unityChan.tkm";
	playerInitData.m_fxFilePath = "Assets/shader/model.fx";
	//モデルにぶち込むぜ。
	playerModel.Init(playerInitData);
}

Player::~Player()
{
}

bool Player::Start()
{
	return true;
}
//更新関数
void Player::Update()
{
	RenderUpdate();
}
//描画更新関数。後に消える可能性大。
void Player::RenderUpdate()
{
	playerModel.UpdateWorldMatrix({ -50.0f, 0.0f, 0.0f }, g_quatIdentity, g_vec3One);
}
//移動処理を書いた関数。
void Player::MoveOperation()
{
	float ZERO = 0.0f;
	//stickの入力に合わせて動きます。
	float lStick_x = (g_pad[0]->GetLStickXF());
	float lStick_z = (g_pad[0]->GetLStickYF());
	//カメラの前方方向
	cameraForward = g_camera3D->GetForward();
	cameraRight = g_camera3D->GetRight();
	//XZ平面での前方方向、右方向に変換
	cameraForward.y = ZERO;
	cameraForward.Normalize();
	cameraRight.y = ZERO;
	cameraRight.Normalize();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	//移動。
	
}