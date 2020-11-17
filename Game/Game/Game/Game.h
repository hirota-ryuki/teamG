#pragma once

class Player;
class GameCamera;
class RenderContext;
class BackGround;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	/// <summary>
	/// ゲームのインスタンスを取得。
	/// </summary>
	/// <returns>ゲームのインスタンス</returns>
	static Game* GetGame()
	{
		return m_game;
	}
	/// <summary>
	/// プレイヤーのインスタンスを取得。
	/// </summary>
	/// <returns>プレイヤーのインスタンス。</returns>
	Player* GetPlayer() {
		return m_player;
	}
private:
	//インスタンス関係。
	static Game*	m_game;							//Gameクラスのインスタンス。
	Player*			m_player = nullptr;				//プレイヤー。
	GameCamera*		m_gameCamera = nullptr;			//カメラ。
	BackGround*		m_bg = nullptr;					//背景。
};

