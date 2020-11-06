#pragma once



class ICollider;

//���̏��B
struct RigidBodyInfo {

	Vector3 pos = Vector3::Zero;			//���W�B
	Quaternion rot = Quaternion::Identity;	//��]�B
	ICollider* collider = nullptr;				//�R���C�_�[�B
	float mass = 0.0f;							//���ʁB

};
//���̃N���X�B
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//���́B
	btDefaultMotionState*	myMotionState = nullptr;	//���[�V�����X�e�[�g�B
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
};

