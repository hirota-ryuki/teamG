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
	playerModel = NewGO<SkinModelRender>();
	//モデルにぶち込むぜ。
	playerModel->Init("Assets/modelData/unityChan.tkm");
	playerModel->SetPos(m_position);
	//キャラコンの初期化
	m_charaCon.Init(
		80.f,
		200.f,
		m_position
	);
	return true;
}
//更新関数
void Player::Update()
{
	MoveOperation();				//移動処理。
	PlayerInputProcessing();		//入力処理。
}
//移動処理を書いた関数。
void Player::MoveOperation()
{
	const float HALF = 0.5f;			//0.5です。
	//stickの入力に合わせて動きます。
	float lStick_x = (g_pad[0]->GetLStickXF());
	float lStick_z = (g_pad[0]->GetLStickYF());
	//カメラから移動の処理に加える前方と左右の値取得。
	GetCameraVector();
	//XZ成分の移動速度をクリア。
	m_moveSpeed.x = ZERO;
	m_moveSpeed.z = ZERO;
	//移動。
	if (HALF < g_pad[0]->GetLStickXF() || HALF > g_pad[0]->GetLStickYF())
	{
		m_moveSpeed += (cameraForward * m_speed * lStick_x) * m_runSpeed;
		m_moveSpeed += (cameraRight * m_speed * lStick_z) * m_runSpeed;
	}
	//モデル映してます。
	//m_position = m_charaCon.Execute(60 / 1, m_moveSpeed);
	playerModel->SetPos(m_position);
	m_position = m_moveSpeed;
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