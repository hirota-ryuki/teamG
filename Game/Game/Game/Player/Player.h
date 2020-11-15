#pragma once
#include "CharaCon/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// ���߂̈���B
	/// </summary>
	/// <returns></returns>
	bool Start()override;
	/// <summary>
	/// �v���C���[�̍X�V�֐��B
	/// </summary>
	void Update()override;
	/// <summary>
	/// �v���C���[�̈ړ��������������֐��B
	/// </summary>
	void MoveOperation();
	/// <summary>
	/// �`��̍X�V�֐��B
	/// </summary>
	void RenderUpdate();
	/// <summary>
	/// �ړ������̒��ŃJ�����̑O���ƍ��E�̎擾���邽�߂̊֐��B
	/// </summary>
	void GetCameraVector();
	/// <summary>
	/// �v���C���[�̃R���g���[���[���͂̏����B
	/// </summary>
	void PlayerInputProcessing();
private:
	//�v���C���[�̃��f�����������񈬂�܂��B
	ModelInitData playerInitData;
	//�v���C���[�̃��f���B
	Model playerModel;
	//�v���C���[�̃|�W�V����
	Vector3 m_position = Vector3::Zero;
	//�v���C���[�̃X�s�[�h������
	Vector3 m_moveSpeed = Vector3::Zero;
	//�J�����O�������ƉE�����擾�p�B
	Vector3 cameraForward = Vector3::Zero;
	Vector3 cameraRight = Vector3::Zero;
	//��]
	Quaternion m_rotation = Quaternion::Identity;
	//�傫��
	Vector3 m_scale = {1.0f,1.0f,1.0f};
	//�ړ����x�B
	float m_speed = 450.0f;
	//����Ƃ��ɑ����|����ϐ��B
	int m_runSpeed = 1;
	//�}�W�b�N�i���o�[��h���[���B
	const float ZERO = 0.0f;		
	CharacterController m_charaCon;								//�L�����N�^�[�R���g���[���[�B

};

