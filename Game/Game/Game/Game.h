#pragma once

class Player;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	/// <summary>
	/// �����[�Ƃ���񂶂��΂�΂�֐�
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// �Q�[���Ń��[�v������̂Ԃ����݊֐�
	/// </summary>
	void Update()override;
private:
	//�v���C���[
	Player* m_player;
};

