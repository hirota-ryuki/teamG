#pragma once
#include "DebugWireframe.h"
#include "character/CharacterController.h"

class RigidBody;

class PhysicsWorld
{
	btDefaultCollisionConfiguration*		collisionConfig = nullptr;
	btCollisionDispatcher*					collisionDispatcher = nullptr;	//!<�Փˉ��������B
	btBroadphaseInterface*					overlappingPairCache = nullptr;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
	btSequentialImpulseConstraintSolver*	constraintSolver = nullptr;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
	btDiscreteDynamicsWorld*				dynamicWorld = nullptr;			//!<���[���h�B
public:
	~PhysicsWorld();
	void Init();
	void Update();
	void Release();
	/*!
	* @brief	�_�C�i�~�b�N���[���h���擾�B
	*/
	btDiscreteDynamicsWorld* GetDynamicWorld()
	{
		return dynamicWorld;
	}
	/*!
	* @brief	���̂�o�^�B
	*/
	void AddRigidBody(RigidBody& rb);
	/*!
	* @brief	���̂�j���B
	*/
	void RemoveRigidBody(RigidBody& rb);
	void ConvexSweepTest(
		const btConvexShape* castShape,
		const btTransform& convexFromWorld,
		const btTransform& convexToWorld,
		btCollisionWorld::ConvexResultCallback& resultCallback,
		btScalar allowedCcdPenetration = 0.0f
	)
	{
		dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
	}
	void ContactText(
		btCollisionObject* colObj, 
		btCollisionWorld::ContactResultCallback& resultCallback
	)
	{
		dynamicWorld->contactTest(colObj, resultCallback);
	}
	/*!
		* @brief	�R���W�����I�u�W�F�N�g�����[���h�ɓo�^�B
		*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
		*/
	void AddCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->addCollisionObject(&colliObj);
	}
	/*!
	* @brief	�R���W�����I�u�W�F�N�g�����[���h����폜�B
	*@param[in]	colliObj	�R���W�����I�u�W�F�N�g�B
	*/
	void RemoveCollisionObject(btCollisionObject& colliObj)
	{
		dynamicWorld->removeCollisionObject(&colliObj);
	}
	/// <summary>
	/// �f�o�b�O���C���[�t���[����`�悷��֐�
	/// </summary>
	void DebugDraw();
	void ContactTest(
		btCollisionObject* colObj,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
	void ContactTest(
		RigidBody& rb,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);

	void ContactTest(
		CharacterController& charaCon,
		std::function<void(const btCollisionObject& contactCollisionObject)> cb
	);
private:
	DebugWireframe dw;
};

extern PhysicsWorld g_physics;

