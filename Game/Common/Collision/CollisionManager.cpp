/**
 * @file   CollisionManager.cpp
 *
 * @brief  �w�w�w�w�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "CollisionManager.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
CollisionManager::CollisionManager()
	:m_graphics{Graphics::GetInstance()}
{

}



/**
 * @brief �f�X�g���N�^
 */
CollisionManager::~CollisionManager()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void CollisionManager::Initialize()
{

}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void CollisionManager::Update()
{

}



/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void CollisionManager::Draw()
{
	ID3D11DeviceContext*		 context = m_graphics->GetDeviceResources()->GetD3DDeviceContext();
	DirectX::DX11::CommonStates* states  = m_graphics->GetCommonStates();
	DirectX::SimpleMath::Matrix  view    = m_graphics->GetViewMatrix();
	DirectX::SimpleMath::Matrix  proj    = m_graphics->GetProjectionMatrix();
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void CollisionManager::Finalize()
{

}

DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Box* box, Sphere* sphere)
{
    DirectX::SimpleMath::Vector3 boxMin = box->GetCenter() - box->GetHalfSize();
    DirectX::SimpleMath::Vector3 boxMax = box->GetCenter() + box->GetHalfSize();
    DirectX::SimpleMath::Vector3 sphereCenter = sphere->GetCenter();

    // AABB�̍ł��߂��_���v�Z
    float closestX = std::max(boxMin.x, std::min(sphereCenter.x, boxMax.x));
    float closestY = std::max(boxMin.y, std::min(sphereCenter.y, boxMax.y));
    float closestZ = std::max(boxMin.z, std::min(sphereCenter.z, boxMax.z));

    // ���̒��S�ƍł��߂��_�̃x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 collisionVector = {
        sphereCenter.x - closestX,
        sphereCenter.y - closestY,
        sphereCenter.z - closestZ
    };

    // �x�N�g���̒������v�Z
    float distance = sqrt(collisionVector.x * collisionVector.x +
        collisionVector.y * collisionVector.y +
        collisionVector.z * collisionVector.z);

    // �����o������
    if (distance > 0.0f) {
        float overlap = sphere->GetRadius() - distance;
        collisionVector.x /= distance;
        collisionVector.y /= distance;
        collisionVector.z /= distance;

        sphereCenter.x += collisionVector.x * overlap;
        sphereCenter.y += collisionVector.y * overlap;
        sphereCenter.z += collisionVector.z * overlap;
    }
	return sphereCenter;
}
