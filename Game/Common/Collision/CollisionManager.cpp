/**
 * @file   CollisionManager.cpp
 *
 * @brief  �����蔻��Ǘ��Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "CollisionManager.h"

// �N���X�̐ÓI�����o�ϐ��̏�����
std::unique_ptr<CollisionManager> CollisionManager::s_collisionManager = nullptr;

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



CollisionManager* const CollisionManager::GetInstance()
{
	if (s_collisionManager == nullptr)
	{
		//ResourceManager�I�u�W�F�N�g�𐶐����A���̃|�C���^��s_collisionManager�Ɋi�[����
		s_collisionManager.reset(new CollisionManager());
	}
	return s_collisionManager.get();
}



/**
 * @brief �I�u�W�F�N�g�̓o�^
 *
 * @param[in] obj �I�u�W�F�N�g
 *
 * @return �Ȃ�
 */
void CollisionManager::Register(GameObject* obj)
{
	m_objects.push_back(obj);
}



void CollisionManager::AllRelease()
{
	m_objects.clear();
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
 * @brief �����蔻�葍�`�F�b�N
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void CollisionManager::CollisionCheck()
{
	// �����œo�^���ꂽ���ׂẴI�u�W�F�N�g�ɑ΂��ē����蔻����s��
	for (std::list<GameObject*>::iterator it1 = m_objects.begin(); it1 != m_objects.end(); ++it1)
	{
		//�����蔻�肪�L���ł͂Ȃ�������X�L�b�v
		if (!(*it1)->GetShape()->IsEnabled()) 
		{
			continue;
		}
		
		for (std::list<GameObject*>::iterator it2 = std::next(it1); it2 != m_objects.end(); ++it2)
		{
			//�����蔻�肪�L���ł͂Ȃ�������X�L�b�v
			if (!(*it2)->GetShape()->IsEnabled())
			{
				continue;
			}


			GameObject* obj1 = *it1;
			GameObject* obj2 = *it2;
			// �I�u�W�F�N�g���m�̓����蔻����s��
			if (obj1->GetShape()->Intersects(obj2->GetShape())) 
			{
				// �����蔻�肪���������ꍇ�̏���
				obj1->CollisionResponce(obj2);
				obj2->CollisionResponce(obj1);	
				
			}
		}
	}
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

/**
 * @brief ����AABB�̉����o������
 *
 * @param[in] box AABB
 * @param[in] sphere ��(�����o����鑤)
 *
 * @return �����o���ꂽ���̒��S�ʒu
 */
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

/**
 * @brief AABB���m�̉����o������
 *
 * @param[in] box AABB1
 * @param[in] box2 AABB2 (�����o����鑤)
 *
 * @return �����o���ꂽAABB2�̒��S�ʒu
 */
DirectX::SimpleMath::Vector3 CollisionManager::PushOut(Box* box, Box* box2)
{

	DirectX::SimpleMath::Vector3 box1Min = box->GetCenter() - box->GetHalfSize();
	DirectX::SimpleMath::Vector3 box1Max = box->GetCenter() + box->GetHalfSize();
	DirectX::SimpleMath::Vector3 box2Min = box2->GetCenter() - box2->GetHalfSize();
	DirectX::SimpleMath::Vector3 box2Max = box2->GetCenter() + box2->GetHalfSize();
	// AABB�̏d�Ȃ���v�Z
	float overlapX = std::min(box1Max.x, box2Max.x) - std::max(box1Min.x, box2Min.x);
	float overlapY = std::min(box1Max.y, box2Max.y) - std::max(box1Min.y, box2Min.y);
	float overlapZ = std::min(box1Max.z, box2Max.z) - std::max(box1Min.z, box2Min.z);
	// �����o������������
	DirectX::SimpleMath::Vector3 pushOutDirection;
	if (overlapX < overlapY && overlapX < overlapZ) {
		pushOutDirection.x = (box1Max.x > box2Max.x) ? overlapX : -overlapX;
		pushOutDirection.y = 0.0f;
		pushOutDirection.z = 0.0f;
	}
	else if (overlapY < overlapX && overlapY < overlapZ) {
		pushOutDirection.x = 0.0f;
		pushOutDirection.y = (box1Max.y > box2Max.y) ? overlapY : -overlapY;
		pushOutDirection.z = 0.0f;
	}
	else {
		pushOutDirection.x = 0.0f;
		pushOutDirection.y = 0.0f;
		pushOutDirection.z = (box1Max.z > box2Max.z) ? overlapZ : -overlapZ;
	}
	// �����o������
	return box2->GetCenter() + pushOutDirection * 0.5f; // ���S�ʒu���X�V
}
