/*!
 * @brief	�S�[�X�g�I�u�W�F�N�g�B
 */

#pragma once
#include "physics/PhysicsObjectBase.h"

namespace hrEngine{
	/*!
	 * @brief	�S�[�X�g�I�u�W�F�N�g
	 *@detail
	 * �S�[�X�g�I�u�W�F�N�g�͍��̂����蔲���邠���蔻��̃I�u�W�F�N�g�ł��B
	 * �L�����N�^�[�̃`�F�b�N�|�C���g�ʉߔ���A�N���A����Ȃǂ�
	 * �L�����N�^�[�����蔲����K�v�̂��邠���蔻��Ɏg���܂��B
	 */
	class CPhysicsGhostObject : public CPhysicsObjectBase{
	public:
		~CPhysicsGhostObject()
		{
			Release();
		}
		/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃS�[�X�g�I�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
		void Release() override final;
		/*!
		* @brief	�����œn���ꂽ�S�[�X�g�I�u�W�F�N�g���������g���ǂ�������B
		*/
		bool IsSelf(const btCollisionObject& ghost) const
		{
			return &ghost == &m_ghostObject;
		}
		/// <summary>
		/// //�S�[�X�g�̏Փ˔���B
		/// </summary>
		/// <param name="colObj">�R���W�����B</param>
		/// <returns>���茋�ʁB</returns>
		bool IsHit(btCollisionObject* colObj) {
			PhysicsWorld().ContactTest(colObj, [&](const btCollisionObject& contactObject) {
				if (IsSelf(contactObject) == true) {
					return true;
				}
			});
			return false;
		}
		bool IsHit(RigidBody& rb) {
			return IsHit(rb.GetBody());
		}
		bool IsHit(CharacterController& charaCon) {
			return IsHit(*charaCon.GetRigidBody());
		}
		/*!
		* @brief	���W��ݒ�B
		*/
		void SetPosition(const CVector3& pos)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btVector3 btPos;
			pos.CopyTo(btPos);
			btTrans.setOrigin(btPos);
		}
		/*!
		* @brief	��]��ݒ�B
		*/
		void SetRotation(const CQuaternion& rot)
		{
			auto& btTrans = m_ghostObject.getWorldTransform();
			btQuaternion btRot;
			rot.CopyTo(btRot);
			btTrans.setRotation(btRot);
		}
	private:
		/*!
		* @brief	�S�[�X�g�쐬�����̋��ʏ����B
		*/
		void CreateCommon(CVector3 pos, CQuaternion rot) override;
	private:
		bool						m_isRegistPhysicsWorld = false;	//!<�������[���h�ɓo�^���Ă��邩�ǂ����̃t���O�B
		btGhostObject				m_ghostObject;	//!<�S�[�X�g
	};
}