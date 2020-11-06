#pragma once

class Player;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	/// <summary>
	/// すたーとじゃんじゃんばりばり関数
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// ゲームでループするものぶち込み関数
	/// </summary>
	void Update()override;
private:
	//プレイヤー
	Player* m_player;
};

