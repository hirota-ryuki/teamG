#pragma once

class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start()override;
	void Update()override;
private:
	Player* m_player = nullptr;		//�v���C���[�B

	//�ʒu���n
	Vector3 m_position = Vector3::Zero;				//���_�B
	Vector3 m_target = Vector3::Zero;				//�����_�B
	Vector3 m_playerPos = Vector3::Zero;			//�v���C���[�̃|�W�V�����B
	Vector3 m_toPos = { 0.0f, 100.0f, 300.0f };		//�Ǐ]�ɕK�v�ȃ|�W�V�����������Ă���ϐ��B
};

