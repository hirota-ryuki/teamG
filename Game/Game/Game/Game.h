#pragma once

class BackGround;
class GameCamera;
class Player;
class RenderContext;
class Villager;

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
	Villager* GetVillager()
	{
		return m_villager;
	}
private:
	//インスタンス関係。
	static Game*	m_game;							//Gameクラスのインスタンス。
	BackGround*		m_bg = nullptr;					//背景。
	GameCamera*		m_gameCamera = nullptr;			//カメラ。
	Player*			m_player = nullptr;				//プレイヤー。
	Villager*		 m_villager = nullptr;			//村人。
};

