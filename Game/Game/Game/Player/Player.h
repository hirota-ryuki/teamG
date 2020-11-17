#pragma once
#include "CharaCon/CharacterController.h"

class Player : public IGameObject
{
public:
	Player();
	~Player();
	/// <summary>
	/// �v���C���[�̃|�W�V�������擾��������
	/// </summary>
	const Vector3& GetPos() const
	{
		return m_position;
	}
private:
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
	/// ���f���̏������B
	/// </summary>
	void InitModel();
	/// <summary>
	/// �v���C���[�̈ړ��������������֐��B
	/// </summary>
	void MoveOperation();
	/// <summary>
	/// �ړ������̒��ŃJ�����̑O���ƍ��E�̎擾���邽�߂̊֐��B
	/// </summary>
	void GetCameraVector();
	/// <summary>
	/// �v���C���[�̃R���g���[���[���͂̏����B
	/// </summary>
	void PlayerInputProcessing();
	/// <summary>
	/// �v���C���[�̉�]�����B
	/// </summary>
	void PlayerRotation();
private:
	SkinModelRender* playerModel = nullptr;			//�v���C���[�̃��f���B
	CharacterController m_charaCon;					//�L�����N�^�[�R���g���[���[�B

	Vector3 m_position = Vector3::Zero;				//�v���C���[�̃|�W�V�����B
	Vector3 m_moveSpeed = Vector3::Zero;			//�v���C���[�̃X�s�[�h�������B
	Vector3 cameraForward = Vector3::Zero;			//�ړ��Ɏg���J�����O�������擾�B
	Vector3 cameraRight = Vector3::Zero;			//�ړ��Ɏg���J�������E�����擾�B
	Vector3 m_scale = { 1.0f,1.0f,1.0f };			//�傫���B

	Quaternion m_rotation = Quaternion::Identity;	//��Ɏg����]�̕ϐ��B
	Quaternion m_rotating = Quaternion::Identity;	//���f���������Ă�Ƃ��g����]�ϐ��B
	
	const float ZERO = 0.0f;						//�}�W�b�N�i���o�[��h���[���B
	float m_speed = 10.0f;							//�ړ����x�B
		
	int m_runSpeed = 1;								//����Ƃ��ɑ����|����ϐ��B
};

