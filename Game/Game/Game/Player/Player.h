#pragma once
#include "CharaCon/CharacterController.h"

class Villager;
class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// プレイヤーのポジションを取得したい時
	/// </summary>
	const Vector3& GetPos() const
	{
		return m_position;
	}
private:
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
	/// モデルの初期化。
	/// </summary>
	void InitModel();
	/// <summary>
	/// プレイヤーの移動処理が入った関数。
	/// </summary>
	void MoveOperation();
	/// <summary>
	/// 移動処理の中でカメラの前方と左右の取得するための関数。
	/// </summary>
	void GetCameraVector();
	/// <summary>
	/// プレイヤーのコントローラー入力の処理。
	/// </summary>
	void PlayerInputProcessing();
	/// <summary>
	/// プレイヤーの回転処理。
	/// </summary>
	void PlayerRotation();
	/// <summary>
	/// プレイヤーと村人の距離を測る。
	/// </summary>
	void DistanceOfVillagers();
	/// <summary>
	/// プレイヤーの前方ベクトル。 
	/// </summary>
	void Forward();
	/// <summary>
	/// プレイヤーが消えるときに消したいものを入れる
	/// </summary>
	void OnDestroy()override;
private:
	Villager* m_villager = nullptr;					//村人。	

	SkinModelRender* m_playerModel = nullptr;		//プレイヤーのモデル。
	CharacterController m_charaCon;					//キャラクターコントローラー。

	Vector3 m_position = Vector3::Zero;				//プレイヤーのポジション。
	Vector3 m_moveSpeed = Vector3::Zero;			//プレイヤーのスピードを扱う。
	Vector3 m_cameraForward = Vector3::Zero;			//移動に使うカメラ前方方向取得。
	Vector3 m_cameraRight = Vector3::Zero;			//移動に使うカメラ左右方向取得。
	Vector3 m_scale = { 1.0f,1.0f,1.0f };			//大きさ。
	Vector3 m_forward = Vector3::AxisZ;

	Quaternion m_rotation = Quaternion::Identity;	//主に使う回転の変数。
	Quaternion m_rotating = Quaternion::Identity;	//モデルが動いてるとき使う回転変数。

	const float ZERO = 0.0f;						//マジックナンバーを防ぐゼロ。
	float m_speed = 100.0f;							//移動速度。

	int m_runSpeed = 1;								//走るときに速さ掛ける変数。

	bool isHitVillager_flag = false;				//村人と接敵しているか
};

