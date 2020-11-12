/*!
 * @brief	物理オブジェクトのベースクラス。
 */

#include "stdafx.h"
#include "physics/PhysicsObjectBase.h"
#include "physics/BoxCollider.h"
#include "physics/CapsuleCollider.h"
#include "physics/SphereCollider.h"
namespace hrEngine {

	void CPhysicsObjectBase::CreateBox(Vector3 pos, Quaternion rot, Vector3 size)
	{
		Release();
		auto boxCollider = std::make_unique<BoxCollider>();
		boxCollider->Create(size);
		m_collider = move(boxCollider);
		CreateCommon(pos, rot);
	}
	void CPhysicsObjectBase::CreateCapsule(Vector3 pos, Quaternion rot, float radius, float height)
	{
		Release();
		auto capusuleCollider = std::make_unique<CapsuleCollider>();
		capusuleCollider->Create(radius, height);
		m_collider = move(capusuleCollider);
		CreateCommon(pos, rot);
	}

	void CPhysicsObjectBase::CreateSphere(Vector3 pos, Quaternion rot, float radius)
	{
		Release();
		auto sphereCollider = std::make_unique<SphereCollider>();
		sphereCollider->Create(radius);
		m_collider = move(sphereCollider);
		CreateCommon(pos, rot);
	}

	/*void CPhysicsObjectBase::CreateMesh(Vector3 pos, Quaternion rot, const SkinModelData& skinModelData)
	{
		Release();
		auto meshCollider = make_unique<MeshCollider>();
		meshCollider->CreateFromSkinModel(skinModelData, nullptr);
		m_collider = move(meshCollider);
		CreateCommon(pos, rot);
	}*/
	/*void CPhysicsObjectBase::CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, SkinModelRender* skinModelRender)
	{
		CreateMesh(pos, rot, scale, skinModelRender->GetModel());
	}
	void CPhysicsObjectBase::CreateMesh(Vector3 pos, Quaternion rot, Vector3 scale, const SkinModel& skinModel)
	{
		Release();
		CMatrix mScale;
		mScale.MakeScaling(scale);
		auto meshCollider = make_unique<MeshCollider>();
		meshCollider->CreateFromSkinModel(skinModel, &mScale);
		m_collider = move(meshCollider);
		CreateCommon(
			pos,
			rot
		);

	}*/

}