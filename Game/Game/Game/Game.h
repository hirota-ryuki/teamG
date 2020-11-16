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
	/// �����[�Ɗ֐�
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// �Q�[���̃A�v�f
	/// </summary>
	void Update()override;
private:
	Player* m_player = nullptr;					//�v���C���[�B
	GameCamera* m_gameCamera = nullptr;			//�J�����B
	BackGround* m_bg = nullptr;					//�w�i�B
};

