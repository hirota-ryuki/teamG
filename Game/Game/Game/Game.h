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
	/// <summary>
	/// 開始関数。
	/// </summary>
	/// <returns></returns>
	bool Start() override;
	/// <summary>
	/// 更新関数。
	/// </summary>
	void Update() override;
	void OnDestroy() override;
private:
	Player* m_player = nullptr;					//プレイヤー。
	GameCamera* m_gameCamera = nullptr;			//カメラ。
	BackGround* m_bg = nullptr;					//背景。
};

