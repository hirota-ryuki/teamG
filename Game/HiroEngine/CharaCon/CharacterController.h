/*!
* @brief	�L�����N�^�R���g���[���[�B
*/

#pragma once

#include "physics/CapsuleCollider.h"
#include "physics/RigidBody.h"


/*!
* @brief	�L�����N�^�R���g���[���[�B
*/
class CharacterController{
public:
	CharacterController() {

	}
	~CharacterController()
	{
		RemoveRigidBoby();
	}
	/*!
		* @brief	�������B
		*@param[in]	radius			�J�v�Z���R���C�_�[�̔��a�B
		*@param[in]	height			�J�v�Z���R���C�_�[�̍����B
		*@param[in]	position		�����ʒu�B
		*@param[in]	isPassingWall	�Փ˔�����L�����N�^�����s���A�ǂ͍s��Ȃ��悤�ɂ���ݒ�B��{��false�B
		*/
	void Init(float radius, float height, const Vector3& position, bool isPassingWall = false);
	/*!
		* @brief	���s�B
		*@param[in]	deltaTime		�o�ߎ��ԁB�P�ʂ͕b�B
		*@param[in, out]	moveSpeed		�ړ����x�B�����ŏd�͉������v�Z����A���̌��ʂ�moveSpeed�ɔ��f����܂��B
		*@return �ړ���̃L�����N�^�[�̍��W�B
		*/
	const Vector3& Execute(float deltaTime, Vector3& moveSpeed);
	/*!
		* @brief	���W���擾�B
		*/
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/*!
		* @brief	���W��ݒ�B
		*/
	void SetPosition(const Vector3& pos)
	{
		m_position = pos;
	}

	/*!
		* @brief	�W�����v��������
		*/
	bool IsJump() const
	{
		return m_isJump;
	}
	/*!
	* @brief	�n�ʏ�ɂ��邩����B
	*/
	bool IsOnGround() const
	{
		return m_isOnGround;
	}
	/*!
	* @brief	�R���C�_�[���擾�B
	*/
	CapsuleCollider* GetCollider()
	{
		return &m_collider;
	}
	/*!
	* @brief	���̂��擾�B
	*/
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	/*!
	* @brief	���̂𕨗��G���W������폜�B�B
	*/
	void RemoveRigidBoby();
	/// <summary>
	/// �Փ˔�����s�����ǂ����B
	/// �Ă΂ꂽ��true��false�����ւ���B
	/// </summary>
	void ChangeActive()
	{
		m_isActive = !m_isActive;
	}
	/// <summary>
	/// �Փ˔�����s�����ǂ����B
	/// true��false�����w�肷��B
	/// </summary>
	void ActiveMode(bool active)
	{
		m_isActive = active;
	}
private:
	Vector3 			m_position = Vector3::Zero;	//���W�B
	bool 				m_isJump = false;				//�W�����v���H
	bool				m_isOnGround = true;			//�n�ʂ̏�ɂ���H
	bool				m_isActive = true;				//�Փ˔�����s�����ǂ����B�n�ʂƂ̓����蔻��͂���B
	CapsuleCollider		m_collider;						//�R���C�_�[�B
	float				m_radius = 0.0f;
	float				m_height = 0.0f;		
	RigidBody			m_rigidBody;					//���́B
};
