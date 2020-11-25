#pragma once

class Player;
class Game;
class GameCamera : public IGameObject
{
public:

	/// <summary>
	/// �J�����̏�ԁB
	/// </summary>
	enum CameraState {
		toPlayer,
		toPosition1,
		toPosition2
	};
	GameCamera();
	~GameCamera();

	void SetChangeCameraFlag(bool flag)
	{
		isCameraTagChange_flag = flag;
	}
private:
	bool Start()override;
	void Update()override;

	// �J����������������������Ɉڂ��܂����B
	void MoveCamera();
	//�~�܂��Ă��鏈���B
	//���m�ɂ̓}�b�v������ɉf���ꏊ���w�肷�鏈���B
	void StopCamera();
	//	�J�����̎��_��ύX���鏈���B 
	void ChangePointOfView();
	// �J�����̏�ԂŌĂԊ֐���ύX����֐�
	void StateCamera();
private:
	Player* m_player = nullptr;						//�v���C���[�B
	CameraState m_cameraState;						//�J�����̏�ԁB

	Vector3 m_position = Vector3::Zero;				//���_�B
	Vector3 m_target = Vector3::Zero;				//�����_�B
	Vector3 m_toPos = { 0.0f, 225.0f, 200.0f };		//�Ǐ]�ɕK�v�ȃ|�W�V�����������Ă���ϐ��B

	//��ŏ�����\����B
	Vector3 m_position1 = { 25.0f, 50.0f, 100.0f};	//���̕ύX�ꏊ�B
	Vector3 m_target1 = { 25.0f,50.0f, 0.0f};		//���̎��_�ύX�ꏊ�B

	bool isCameraTagChange_flag = false;			//�^�[�Q�b�g�ύX���邩�B
};

