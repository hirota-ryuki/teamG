#pragma once
class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// 初めの一歩。
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// プレイヤーの更新関数。
	/// </summary>
	void Update();
	//移動
	void MoveOperation();
	//更新描画関数
	void RenderUpdate();
private:
	//プレイヤーのモデル生成する情報握ります。
	ModelInitData playerInitData;
	//プレイヤーのモデル。
	Model playerModel;
	//プレイヤーのポジション
	Vector3 m_position = Vector3::Zero;
	//プレイヤーのスピードをあつかうよ～ん
	Vector3 m_moveSpeed = Vector3::Zero;
	//カメラ前方方向と右方向取得用。
	Vector3 cameraForward = Vector3::Zero;
	Vector3 cameraRight = Vector3::Zero;
	//回転
	Quaternion m_rotation = Quaternion::Identity;
	//大きさ
	Vector3 m_scale = {1.0f,1.0f,1.0f};
	//移動速度。
	float m_speed = 450.0f;
};

