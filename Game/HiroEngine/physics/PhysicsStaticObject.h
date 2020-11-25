/*!
 * @brief	�ÓI�I�u�W�F�N�g�B
 */

#pragma once

#include "physics/MeshCollider.h"
#include "physics/RigidBody.h"


/*!
* @brief	�ÓI�����I�u�W�F�N�g
*/
class PhysicsStaticObject{
public:
	/*!
		* @brief	�R���X�g���N�^�B
		*/
	PhysicsStaticObject();
	/*!
		* @brief	�f�X�g���N�^�B
		*/
	~PhysicsStaticObject();
	/*!
		* @brief	���b�V���̐ÓI�I�u�W�F�N�g���쐬�B
		*@param[in]	skinModel	�X�L�����f���B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*/
	void CreateMeshObject(SkinModel& skinModel, Vector3 pos, Quaternion rot);
	/// <summary>
	/// ���[�U�[�C���f�b�N�X��ݒ�B
	/// </summary>
	/// <param name="index">���[�U�[�C���f�b�N�X</param>
	void SetUserIndex(int index){
		m_rigidBody.GetBody()->setUserIndex(index);
	}
	void SetRotation(const Quaternion& rot) {
		btRigidBody* btBody = m_rigidBody.GetBody();
		//���̂𓮂����B
		btBody->setActivationState(DISABLE_DEACTIVATION);
		btTransform& trans = btBody->getWorldTransform();
		trans.setRotation(btQuaternion(rot.x, rot.y, rot.z));
	}
	void ReMove() {
		g_physics.RemoveRigidBody(m_rigidBody);
		m_isReMove = true;
	}
private:
	MeshCollider	m_meshCollider;			//!<���b�V���R���C�_�[�B
	RigidBody		m_rigidBody;			//!<���́B
	bool			m_isReMove = false;		//�����[�u�������ǂ����B
	bool			m_isInit = false;
};
