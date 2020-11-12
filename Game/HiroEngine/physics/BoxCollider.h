/*!
 * @brief	�J�v�Z���R���C�_�[�B
 */

#pragma once

#include "physics/ICollider.h"


class BoxCollider : public ICollider
{
public:
	/*!
	* @brief	�f�X�g���N�^�B
	*/
	~BoxCollider();
	/*!
	* @brief	�쐬�B
	*@param[in] radius	�J�v�Z���̔��a�B
	*@param[in]	height	�J�v�Z���̍����B
	*/
	void Create(Vector3 halfSize)
	{
		btVector3 btSize;
		btSize.setX(halfSize.x);
		btSize.setY(halfSize.y);
		btSize.setZ(halfSize.z);
	
		shape = new btBoxShape(btSize);
		this->radius = radius;
		this->height = height;
	}
	btCollisionShape* GetBody() const override
	{
		return shape;
	}
	float GetRadius() const
	{
		return radius;
	}
	float GetHeight() const
	{
		return height;
	}
private:
	btBoxShape*		shape = nullptr;
	float radius = 0.0f;
	float height = 0.0f;
};
