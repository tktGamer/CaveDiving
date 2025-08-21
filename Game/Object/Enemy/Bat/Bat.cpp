/**
 * @file   Bat.cpp
 *
 * @brief  �R�E�����̓G�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Bat.h"
#include "Game/Common/Collision/CollisionManager.h"
#include"../CaveDiving/Game/Fuctory/CharacterFactory.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Bat::Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:m_graphics{Graphics::GetInstance()}
	, Character(50,5,15,Tag::ObjectType::Enemy, parent, initialPosition, initialAngle)
	, m_objectNumber{ CountUpNumber() }
	, m_sphere{ GetPosition(), 2.0f } // �����ʒu�ƃT�C�Y��ݒ�
	, m_isAlive{ true }
{
	SetTexture(ResourceManager::GetInstance()->RequestTexture("bat.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"bat.sdkmesh"));

	SetShape(&m_sphere);

	m_leftWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{-0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(0.0f));
	m_rightWing = std::make_unique<Wing>(this, DirectX::SimpleMath::Vector3{0.5f,0.0f,0.0f}, DirectX::XMConvertToRadians(180.0f));



}



/**
 * @brief �f�X�g���N�^
 */
Bat::~Bat()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Bat::Initialize()
{
	// ��Ԃ̏�����
	m_idlingState = std::make_unique<BatIdling>(this);
	m_movingState = std::make_unique<BatMoving>(this);
	m_attackState = std::make_unique<BatAttack>(this);
	SetState(m_idlingState.get());


	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -5.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

}



/**
 * @brief �X�V����
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Bat::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	//�����Ă��Ȃ��ꍇ�X�V���Ȃ�
	if (!m_isAlive)
	{
		return;
	}


	//���݂̏�Ԃ��X�V
	GetState()->Update(elapsedTime);


	m_currentPosition = m_initialPosition + currentPosition + GetPosition();
	m_currentAngle = GetQuaternion() * currentAngle;
	m_sphere.SetCenter(m_currentPosition);

	m_leftWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());
	m_rightWing->Update(elapsedTime, GetCurrentPosition(), GetCurrentQuaternion());
}




/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Bat::Draw()
{
	//�����Ă��Ȃ��ꍇ�`�悵�Ȃ�
	if (!m_isAlive) 
	{
		return;
	}


	//���݂̏�Ԃ�`��
	GetState()->Render();

	m_leftWing->Draw();
	m_rightWing->Draw();
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Bat::Finalize()
{

}

void Bat::OnMessegeAccepted(Message::MessageID messageID)
{
}

void Bat::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Player:
		{
			// �v���C���[�Ƃ̏Փˏ���
			// �����ł͉������Ȃ����A�K�v�ɉ����Ď���
			break;
		}
		case Tag::ObjectType::Stage:
		{
			//�X�e�[�W�Ƃ̏Փˉ����@�����o��
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere));
			//���x�����Z�b�g
			m_velocity.y = 0.0f;

			break;
		}
		case Tag::ObjectType::Pikel:
		{
			//�s�b�P���Ƃ̏Փˉ���
			//�Ǘ��N���X�ɍ폜�˗����o��
			m_isAlive = false;

			break;
		}
	default:
		break;
	}
}


int Bat::GetObjectNumber()
{
	return m_objectNumber;
}

DirectX::SimpleMath::Vector3 Bat::GetVelocity()
{
	return m_velocity;
}

void Bat::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}

bool Bat::IsAlive() const
{
	return m_isAlive;
}
