#pragma once
class Player
{
public:
	Player();
	~Player();
	/// <summary>
	/// ���߂̈���B
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �v���C���[�̍X�V�֐��B
	/// </summary>
	void Update();
	//�ړ�
	void MoveOperation();
	//�X�V�`��֐�
	void RenderUpdate();
private:
	//�v���C���[�̃��f�����������񈬂�܂��B
	ModelInitData playerInitData;
	//�v���C���[�̃��f���B
	Model playerModel;
	//�v���C���[�̃|�W�V����
	Vector3 m_position = Vector3::Zero;
	//�v���C���[�̃X�s�[�h����������`��
	Vector3 m_moveSpeed = Vector3::Zero;
	//�J�����O�������ƉE�����擾�p�B
	Vector3 cameraForward = Vector3::Zero;
	Vector3 cameraRight = Vector3::Zero;
	//�ړ����x�B
	float m_speed = 450.0f;
};
