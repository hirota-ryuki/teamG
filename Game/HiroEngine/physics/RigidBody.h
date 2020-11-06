#pragma once



class ICollider;

//剛体情報。
struct RigidBodyInfo {

	Vector3 pos = Vector3::Zero;			//座標。
	Quaternion rot = Quaternion::Identity;	//回転。
	ICollider* collider = nullptr;				//コライダー。
	float mass = 0.0f;							//質量。

};
//剛体クラス。
class RigidBody
{
	btRigidBody*			rigidBody = nullptr;		//剛体。
	btDefaultMotionState*	myMotionState = nullptr;	//モーションステート。
public:

	~RigidBody();
	void Release();
	void Create(RigidBodyInfo& rbInfo);
	btRigidBody* GetBody()
	{
		return rigidBody;
	}
};

