/**
 * @file   AttackMotion.cpp
 *
 * @brief  �U���̃��[�V�����Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "AttackMotion.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
AttackMotion::AttackMotion(Hand* pRightHand, Hand* pLeftHand)
	:m_pRightHand{pRightHand}
	, m_pLeftHand{pLeftHand}
	, m_isNextAttack{ false }
	, m_attackType{ Attack::COMBO1 }
	, m_motionLerp{ 0.0f }
{

}



/**
 * @brief �f�X�g���N�^
 */
AttackMotion::~AttackMotion()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void AttackMotion::Initialize()
{
	
}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return true  �U���I��
 * @return false �U����
 */
bool AttackMotion::Update()
{
	switch (m_attackType) 
	{
	case Attack::COMBO1:
			if (FirstAttack())
			{
				//�U���{�^���������Ă����玟�̍U����
				if (m_isNextAttack)
				{
					m_attackType = Attack::COMBO2;
					m_motionLerp = 0.0f;
					m_isNextAttack = false;
				}
				else 
				{
					//�U���I��
					return true;
				}
			}
			break;
	case Attack::COMBO2:
			if (SecondAttack())
			{
				//�U���{�^���������Ă����玟�̍U����
				if (m_isNextAttack)
				{
					m_attackType = Attack::COMBO3;
					m_motionLerp = 0.0f;
					m_isNextAttack = false;

				}
				else
				{
					//�U���I��
					return true;
				}
			}
			break;
	case Attack::COMBO3:
			if (ThirdAttack())
			{

				//�U���I��
				return true;
			}
			break;
	}

	//�U������false��Ԃ�
	return false;
}





/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void AttackMotion::Reset()
{
	m_isNextAttack = false;
	m_attackType = Attack::COMBO1;
	m_motionLerp = 0.0f;
}

bool AttackMotion::FirstAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	//* DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(45.0f))
	//	DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitZ, DirectX::XMConvertToRadians(-90.0f));

	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	//q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(145.0f));

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();
	//m_pHand->SetQuaternion()
	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

bool AttackMotion::SecondAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;

	DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 5.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

bool AttackMotion::ThirdAttack()
{
	DirectX::SimpleMath::Quaternion start = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f));
	DirectX::SimpleMath::Quaternion end = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(170.0f));
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(TKTLib::Lerp(0.0f, 360.0f, m_motionLerp)));

	//DirectX::SimpleMath::Quaternion::Lerp(start, end, m_motionLerp, q);
	m_motionLerp += 4.0f * Messenger::GetInstance()->GetElapsedTime();

	m_pRightHand->SetMotionAngle(q);


	if (m_motionLerp >= 1.0f)
	{
		return true;
	}
	return false;
}

void AttackMotion::SetIsNextAttack(bool isNext)
{
	m_isNextAttack = isNext;
}
