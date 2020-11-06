#include "stdafx.h"
#include "SphereCollider.h"
/*!
	 * @brief	�R���X�g���N�^�B
	 */
SphereCollider::SphereCollider() :
	shape(NULL)
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
SphereCollider::~SphereCollider()
{
	delete shape;
}
/*!
 * @brief	���̃R���C�_�[���쐬�B
 */
void SphereCollider::Create(const float radius)
{
	shape = new btSphereShape(radius);
}