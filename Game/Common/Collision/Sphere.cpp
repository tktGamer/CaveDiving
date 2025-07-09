/**
 * @file   Sphere.cpp
 *
 * @brief  ����̓����蔻��Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ��@���n�M��
 *
 * @date   ���t 2025/7/02
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Sphere.h"
#include "../Collision/Box.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] center ���S���W
 * @param[in] radius ���a
 */
Sphere::Sphere(DirectX::SimpleMath::Vector3 center, float radius)
	: Shape(ShapeType::Sphere)
	, m_center(center)
	, m_radius(radius)
{
}

/**
 * @brief �f�X�g���N�^
 */
Sphere::~Sphere()
{

}




/**
 * @brief ���̌`��ƏՓ˔�����s��
 *
 * @param[in] other �Փ˔�����s�����̌`��
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Sphere::Intersects(Shape* other)
{

	if (other == nullptr)
	{
		return false;
	}

	//�`��̎�ނ��m�F
	switch (other->GetShapeType())
	{
	case ShapeType::Box:
		return IntersectBox(static_cast<Box*>(other));
		break;
	case ShapeType::Sphere:
		return IntersectSphere(static_cast<Sphere*>(other));
		break;
	default:
		break;
	}


	return false;
}


/**
 * @brief �����蔻��`��N���X�ɒǉ�
 *
 * @param[in] dC �����蔻��`��N���X
 *
 * @return �Ȃ�
 */
void Sphere::AddDisplayCollision(Ito::DisplayCollision* dC)
{
	DirectX::BoundingSphere bs{ m_center,m_radius };
	dC->AddBoundingVolume(bs);
}

/**
 * @brief ���S���W��ݒ肷��
 *
 * @param[in] center ���S���W
 *
 * @return �Ȃ�
 */
void Sphere::SetCenter(const DirectX::SimpleMath::Vector3& center)
{
	m_center = center;
}

/**
 * @brief ���S���W���擾����
 * 
 * @param[in] �Ȃ�
 *
 * @return ���S���W
 */
DirectX::SimpleMath::Vector3 Sphere::GetCenter() const
{
	return m_center;
}

/**
 * @brief ���a��ݒ肷��
 *
 * @param[in] radius ���a
 *
 * @return �Ȃ�
 */
void Sphere::SetRadius(float radius)
{
	m_radius = radius;
}

/**
 * @brief ���a���擾����
 * 
 * @param[in] �Ȃ�
 * 
 * @return ���a
 */
float Sphere::GetRadius() const
{
	return m_radius;
}

/**
 * @brief �����AABB�̏Փ˔�����s��
 *
 * @param[in] other �Փ˔�����s��AABB
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Sphere::IntersectBox(Box* other) const
{
	//����AABB
	DirectX::SimpleMath::Vector3 boxMin = other->GetCenter() - other->GetHalfSize();
	DirectX::SimpleMath::Vector3 boxMax = other->GetCenter() + other->GetHalfSize();

	// AABB�̍ł��߂��_���v�Z
	float x = std::max(boxMin.x, std::min(m_center.x, boxMax.x));
	float y = std::max(boxMin.y, std::min(m_center.y, boxMax.y));
	float z = std::max(boxMin.z, std::min(m_center.z, boxMax.z));

	// ���̒��S�ƍł��߂��_�Ƃ̋����̓����v�Z
	float distanceSquared = (x - m_center.x) * (x - m_center.x) +
							(y - m_center.y) * (y - m_center.y) +
							(z - m_center.z) * (z - m_center.z);

	// �����̓�悪���̔��a�̓��ȉ��ł���Γ�����
	return distanceSquared <= (m_radius * m_radius);

}


/**
 * @brief ����ƏՓ˔�����s��
 *
 * @param[in] other �Փ˔�����s������
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Sphere::IntersectSphere(Sphere* other) const
{
	//���Ƌ��̓����蔻��
	DirectX::SimpleMath::Vector3 distance = m_center - other->GetCenter();
	
	float radiusSum = m_radius + other->GetRadius();
	if (distance.LengthSquared() <= radiusSum * radiusSum)
	{
		return true;
	}
	return false;
}
