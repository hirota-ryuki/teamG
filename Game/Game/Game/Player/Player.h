#pragma once
#include "CharaCon/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// 初めの一歩。
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// プレイヤーの更新関数。
	/// </summary>
	void Update()override;
	/// <summary>
	/// プレイヤーの移動処理が入った関数。
	/// </summary>
	void MoveOperation();
	/// <summary>
	/// 描画の更新関数。
	/// </summary>
	void RenderUpdate();
	/// <summary>
	/// 移動処理の中でカメラの前方と左右の取得するための関数。
	/// </summary>
	void GetCameraVector();
	/// <summary>
	/// プレイヤーのコントローラー入力の処理。
	/// </summary>
	void PlayerInputProcessing();
private:
	//プレイヤーのモデル生成する情報握ります。
	ModelInitData playerInitData;
	//プレイヤーのモデル。
	Model playerModel;
	//プレイヤーのポジション
	Vector3 m_position = Vector3::Zero;
	//プレイヤーのスピードを扱う
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
	//走るときに速さ掛ける変数。
	int m_runSpeed = 1;
	//マジックナンバーを防ぐゼロ。
	const float ZERO = 0.0f;		
	CharacterController m_charaCon;								//キャラクターコントローラー。

};

