#pragma once

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;
/// <summary>
/// �v���C���[���Q�ƁB
/// </summary>
	void BindPlayer(Player* pl)
	{
		m_player = pl;
	}
private:
	Player* m_player = nullptr;		//�v���C���[�B

	//�ʒu���n
	Vector3 m_position;				//���_�B
	Vector3 m_target;				//�����_�B
	Vector3 m_playerPos;			//�v���C���[�̃|�W�V�����B
};

