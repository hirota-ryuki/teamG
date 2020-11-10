#pragma once

class Player;
class RenderContext;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	/// <summary>
	/// すたーと関数
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// ゲームのアプデ
	/// </summary>
	void Update()override;

private:
	//プレイヤー
	Player* m_player;
};

