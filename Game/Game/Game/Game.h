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
	/// �Q�[���̃C���X�^���X���擾�B
	/// </summary>
	/// <returns>�Q�[���̃C���X�^���X</returns>
	static Game* GetGame()
	{
		return m_game;
	}
	/// <summary>
	/// �v���C���[�̃C���X�^���X���擾�B
	/// </summary>
	/// <returns>�v���C���[�̃C���X�^���X�B</returns>
	Player* GetPlayer() {
		return m_player;
	}
private:
	//�C���X�^���X�֌W�B
	static Game*	m_game;							//Game�N���X�̃C���X�^���X�B
	Player*			m_player = nullptr;				//�v���C���[�B
	GameCamera*		m_gameCamera = nullptr;			//�J�����B
	BackGround*		m_bg = nullptr;					//�w�i�B
};

