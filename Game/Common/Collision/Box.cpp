/**
 * @file   Box.cpp
 *
 * @brief  AABB�̓����蔻��Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ��@���n�M��
 *
 * @date   ���t 2025/7/02
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Box.h"


#include "../Collision/Sphere.h"
// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] center ���S���W
 * @param[in] halfSize �����̃T�C�Y
 * 
 */
Box::Box(DirectX::SimpleMath::Vector3 center, DirectX::SimpleMath::Vector3 halfSize)
	:Shape(ShapeType::Box)
	, m_center(center)
	, m_halfSize(halfSize)
{
}

/**
 * @brief �f�X�g���N�^
 */
Box::~Box()
{

}




/**
 * @brief ���̌`��ƏՓ˔�����s��
 *
 * @param[in] other �Փ˔�����s�����̌`��
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Box::Intersects(Shape* other)
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




void Box::AddDisplayCollision(Ito::DisplayCollision* dC)
{
	DirectX::BoundingBox bb{ m_center,m_halfSize };
	dC->AddBoundingVolume(bb);
}

/**
 * @brief ���S���W��ݒ肷��
 *
 * @param[in] center ���S���W
 *
 * @return �Ȃ�
 */
void Box::SetCenter(const DirectX::SimpleMath::Vector3& center)
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
DirectX::SimpleMath::Vector3 Box::GetCenter() const
{
	return m_center;
}

/**
 * @brief �����̃T�C�Y��ݒ肷��
 *
 * @param[in] halfSize �����̃T�C�Y
 *
 * @return �Ȃ�
 */
void Box::SetHalfSize(const DirectX::SimpleMath::Vector3& halfSize)
{
	m_halfSize = halfSize;
}


/**
 * @brief �����̃T�C�Y���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return �����̃T�C�Y
 */
DirectX::SimpleMath::Vector3 Box::GetHalfSize() const
{
	return m_halfSize;
}

/**
 * @brief ����AABB�ƏՓ˔�����s��
 *
 * @param[in] other �Փ˔�����s������AABB
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Box::IntersectBox(Box* other)
{
	DirectX::SimpleMath::Vector3 thiMin = m_center - m_halfSize;
	DirectX::SimpleMath::Vector3 thiMax = m_center + m_halfSize;
	DirectX::SimpleMath::Vector3 otherMin = other->GetCenter() - other->GetHalfSize();
	DirectX::SimpleMath::Vector3 otherMax = other->GetCenter() + other->GetHalfSize();
	// AABB�̏Փ˔�����s��

	if (thiMin.x > otherMax.x || thiMax.x < otherMin.x ||
		thiMin.y > otherMax.y || thiMax.y < otherMin.y ||
		thiMin.z > otherMax.z || thiMax.z < otherMin.z)
	{
		return false; // �Փ˂��Ă��Ȃ�
	}

	return true;
}

/**
 * @brief ���ƏՓ˔�����s��
 *
 * @param[in] other �Փ˔�����s����
 *
 * @return �Փ˂��Ă��邩�ǂ���
 */
bool Box::IntersectSphere(Sphere* other) const
{
	//����AABB
	DirectX::SimpleMath::Vector3 boxMin = m_center - m_halfSize;
	DirectX::SimpleMath::Vector3 boxMax = m_center + m_halfSize;
	DirectX::SimpleMath::Vector3 sphereCenter = other->GetCenter();
	// AABB�̍ł��߂��_���v�Z
	float x = std::max(boxMin.x, std::min(sphereCenter.x, boxMax.x));
	float y = std::max(boxMin.y, std::min(sphereCenter.y, boxMax.y));
	float z = std::max(boxMin.z, std::min(sphereCenter.z, boxMax.z));

	// ���̒��S�ƍł��߂��_�Ƃ̋����̓����v�Z
	float distanceSquared = (x - sphereCenter.x) * (x - sphereCenter.x) +
							(y - sphereCenter.y) * (y - sphereCenter.y) +
							(z - sphereCenter.z) * (z - sphereCenter.z);

	// �����̓�悪���̔��a�̓��ȉ��ł���Γ�����
	return distanceSquared <= (other->GetRadius() * other->GetRadius());

}
