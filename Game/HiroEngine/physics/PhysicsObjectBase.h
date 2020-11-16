/*!
 *@brief	�����I�u�W�F�N�g�̃x�[�X�N���X�B
 */
#pragma once
#include "ICollider.h"

namespace hrEngine {

	/*!
	 *@brief	�����I�u�W�F�N�g�̃x�[�X�N���X�B
	 *@detail
	 * template method�p�^�[��
	 */
	class CPhysicsObjectBase {
	public:
		/*!
		* @brief	�S�[�X�g�I�u�W�F�N�g������B
		*@detail
		* �����I�ȃ^�C�~���O�ŃI�u�W�F�N�g���폜�������ꍇ�ɌĂяo���Ă��������B
		*/
		virtual void Release() = 0;
	private:
		/*!
		* @brief	�ÓI�����I�u�W�F�N�g�쐬�����̋��ʏ����B
		*/
		virtual void CreateCommon(Vector3 pos, Quaternion rot) = 0;
	public:
		/*!
		 *@brief	�R���X�g���N�^�B
		 */
		CPhysicsObjectBase()
		{
		}
		/*!
		 *@brief	�f�X�g���N�^�B
		 */
		virtual ~CPhysicsObjectBase()
		{

		}
		/*!
		 * @brief	�{�b�N�X�`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	size		�T�C�Y�B
		 */
		void CreateBox(Vector3 pos, Quaternion rot, Vector3 size);
		/*!
		 * @brief	�J�v�Z���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		 *@param[in]	pos			���W�B
		 *@param[in]	rot			��]�B
		 *@param[in]	radius		�J�v�Z���̔��a�B
		 *@param[in]	height		�J�v�Z���̍����B
		 */
		void CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height);
		/*!
		* @brief	���̌`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos			���W�B
		*@param[in]	rot			��]�B
		*@param[in]	radius		���̂̔��a�B
		*/
		void CreateSphere(Vector3 pos, Quaternion rot, float radius);
		/*!
		* @brief	���b�V���`��̃S�[�X�g�I�u�W�F�N�g���쐬�B
		*@param[in]	pos					���W�B
		*@param[in]	rot					��]�B
		*@param[in]	skinModelData		�X�L�����f���f�[�^�B
		*/
		//void CreateMesh(Vector3 pos, Quaternion rot, const CSkinModelData& skinModelData);
		/*void CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, const SkinModel& skinModel);
		void CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, SkinModelRender* skinModelRender);*/
	protected:
		std::unique_ptr<ICollider> m_collider;	//!<�R���C�_�[�B
	};
}