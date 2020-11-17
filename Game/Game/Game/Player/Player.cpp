#include "stdafx.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Start()
{
	//モデルの初期化。
	InitModel();
	//キャラコンの初期化。
	m_charaCon.Init(80.f, 200.f, m_position);
	return true;
}
//更新関数。
void Player::Update()
{
	MoveOperation();				//移動処理。
	PlayerRotation();				//回転処理。
	//PlayerInputProcessing();		//入力処理。
}
//モデル呼び出し
void Player::InitModel()
{
	playerModel = NewGO<SkinModelRender>();
	playerModel->Init("Assets/modelData/unityChan.tkm");
	playerModel->SetPos(m_position);
}
//移動処理を書いた関数。
void Player::MoveOperation()
{

	//左スティックの入力量を受け取る。
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();

	//カメラの前方方向と右方向を取得。
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();

	//XZ平面での前方方向、右方向に変換する。
	cameraForward.y = ZERO;
	cameraForward.Normalize();
	cameraRight.y = ZERO;
	cameraRight.Normalize();

	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	//m_moveSpeed.y -= 240.f * 1.f / 60.f;
	m_moveSpeed -= cameraForward * lStick_y * m_speed;		//奥方向への移動速度を代入。
	m_moveSpeed -= cameraRight * lStick_x * m_speed;		//右方向への移動速度を加算。
	m_position = m_charaCon.Execute(1.f / 60.f, m_moveSpeed);
	playerModel->SetPos(m_position);


}
//移動時にカメラから取得するもの。
void Player::GetCameraVector()
{
	//カメラの前方方向
	cameraForward = g_camera3D->GetForward();
	cameraRight = g_camera3D->GetRight();

	//XZ平面での前方方向、右方向に変換
	cameraForward.y = ZERO;
	cameraForward.Normalize();
	cameraRight.y = ZERO;
	cameraRight.Normalize();
}
//コントローラー入力処理。
void Player::PlayerInputProcessing()
{
	const int RUNSPEED = 2;
	//Aボタンが押されたとき。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//話しかけたり、物を拾ったり、基本的に選択するときにOKサイン出す。
		//ただ今、選択物がないため処理が未完成。後々追加されるであろう。
	}
	//Bボタンが押されたとき。
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//移動のスピード上げます。
		m_runSpeed = RUNSPEED;
	}
}
//プレイヤーの回転処理。
void Player::PlayerRotation()
{
	//動いている方向に向く処理
	float m_rot = atan2(m_moveSpeed.x, m_moveSpeed.z);
	m_rotating.SetRotation(Vector3::AxisY, m_rot);

	//移動に合わせて回転の処理
	if (m_moveSpeed.x != ZERO || m_moveSpeed.z != ZERO)
	{
		m_rotation = m_rotating;
		playerModel->SetRot(m_rotation);
	}
	else if(m_moveSpeed.x == ZERO || m_moveSpeed.z == ZERO)
	{
		playerModel->SetRot(m_rotation);
	}
}