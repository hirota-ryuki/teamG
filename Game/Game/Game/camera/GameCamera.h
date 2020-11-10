#pragma once

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;
/// <summary>
/// プレイヤーを参照。
/// </summary>
	void BindPlayer(Player* pl)
	{
		m_player = pl;
	}
private:
	Player* m_player = nullptr;		//プレイヤー。

	//位置情報系
	Vector3 m_position;				//視点。
	Vector3 m_target;				//注視点。
	Vector3 m_playerPos;			//プレイヤーのポジション。
};

