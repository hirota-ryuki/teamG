#pragma once

class Player;
class RenderContext;
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
	//�v���C���[
	Player* m_player;
};

