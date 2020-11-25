#pragma once

class Player;
class Game;
class GameCamera : public IGameObject
{
public:

	/// <summary>
	/// カメラの状態。
	/// </summary>
	enum CameraState {
		toPlayer,
		toPosition1,
		toPosition2
	};
	GameCamera();
	~GameCamera();

	void SetChangeCameraFlag(bool flag)
	{
		isCameraTagChange_flag = flag;
	}
private:
	bool Start()override;
	void Update()override;

	// カメラが動く処理をこちらに移しました。
	void MoveCamera();
	//止まっている処理。
	//正確にはマップ解放時に映す場所を指定する処理。
	void StopCamera();
	//	カメラの視点を変更する処理。 
	void ChangePointOfView();
	// カメラの状態で呼ぶ関数を変更する関数
	void StateCamera();
private:
	Player* m_player = nullptr;						//プレイヤー。
	CameraState m_cameraState;						//カメラの状態。

	Vector3 m_position = Vector3::Zero;				//視点。
	Vector3 m_target = Vector3::Zero;				//注視点。
	Vector3 m_toPos = { 0.0f, 225.0f, 200.0f };		//追従に必要なポジションを持っている変数。

	//後で消える可能性大。
	Vector3 m_position1 = { 25.0f, 50.0f, 100.0f};	//仮の変更場所。
	Vector3 m_target1 = { 25.0f,50.0f, 0.0f};		//仮の視点変更場所。

	bool isCameraTagChange_flag = false;			//ターゲット変更するか。
};

