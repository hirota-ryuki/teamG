#pragma once

class Player;
class GameCamera;
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
	Player* m_player = nullptr;					//プレイヤー。
	GameCamera* m_gameCamera = nullptr;			//カメラ。
};

