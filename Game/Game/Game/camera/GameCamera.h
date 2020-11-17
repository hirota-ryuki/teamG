#pragma once

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;
private:
	Player* m_player = nullptr;		//プレイヤー。

	//位置情報系
	Vector3 m_position = Vector3::Zero;				//視点。
	Vector3 m_target = Vector3::Zero;				//注視点。
	Vector3 m_playerPos = Vector3::Zero;			//プレイヤーのポジション。
	Vector3 m_toPos = { 0.0f, 100.0f, 300.0f };		//追従に必要なポジションを持っている変数。
};

