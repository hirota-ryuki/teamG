#pragma once

class BackGround;
class GameCamera;
class Player;
class RenderContext;
class Villager;
class Title;

class Game : public IGameObject
{
public:
	Game();
	~Game();
public:
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
	Villager* GetVillager()
	{
		return m_villager;
	}
private:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void FlagUpdate();
	void GameMenuFlag();
private:
	//�C���X�^���X�֌W�B
	static Game*	m_game;							//Game�N���X�̃C���X�^���X�B
	BackGround*		m_bg		= nullptr;			//�w�i�B
	GameCamera*		m_gameCamera= nullptr;			//�J�����B
	Player*			m_player	= nullptr;			//�v���C���[�B
	Villager*		m_villager	= nullptr;			//���l�B
	SpriteRender*	m_menu		= nullptr;			//�摜�����_�[�B

	bool isGameMenu_flag		= false;			//���j���[���J���t���O�B
	bool isSpriteCreat_flag		= true;				//���j���[��ʂ���x���������������̂ŁB
	bool isGameDelete_flag		= false;			//�Q�[���I�����邩�̃t���O�B
};

