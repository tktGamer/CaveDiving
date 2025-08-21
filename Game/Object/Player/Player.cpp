/**
 * @file   Player.cpp
 *
 * @brief  �w�w�w�w�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Player.h"

#include "Game/Interface/IState.h"
#include"Game/Shader.h"
#include"Game/Common/Collision/Sphere.h"
#include"Game/Common/Collision/CollisionManager.h"

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] modelParms ���f���p�����[�^
 */
Player::Player(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: Character(100,10,10,Tag::ObjectType::Player,parent,initialPosition,initialAngle)
	, m_objectNumber{ -1 }
	, m_messageID{  }
	, m_velocity{ 0.0f, 0.0f, 0.0f }
	, m_pGem{}
	, m_initialeDirection{ 0.0f, 0.0f, -1.0f }
	, m_sphere{ GetPosition(), 2.0f }
{
	Messenger::GetInstance()->Register(m_objectNumber, this);
}



/**
 * @brief �f�X�g���N�^
 */
Player::~Player()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Player::Initialize()
{
	std::unique_ptr<Hand> handR = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ 1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	std::unique_ptr<Hand> handL = std::make_unique<Hand>(this, DirectX::SimpleMath::Vector3{ -1.5f,0.0f,0.0f }, DirectX::XMConvertToRadians(0.0f));
	// ��Ԃ̏�����
	m_idlingState = std::make_unique<PlayerIdling>(this);
	m_movingState = std::make_unique<PlayerMoving>(this);
	m_attackState = std::make_unique<PlayerAttack>(this,handR.get());
	m_jumpingState = std::make_unique<PlayerJumping>(this);

	m_bodyParts.emplace_back(std::move(handR));
	m_bodyParts.back()->Initialize();
	m_bodyParts.emplace_back(std::move(handL));
	SetState(m_idlingState.get());

	
	SetTexture(ResourceManager::GetInstance()->RequestTexture("player.png"));

	SetModel(ResourceManager::GetInstance()->RequestModel(L"player.sdkmesh"));
	SetPosition(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f));
	SetQuaternion(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0.0f)));
	SetScale(DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));

	SetShape(&m_sphere);

	m_light = std::make_unique<Light>(this,GetPosition(),DirectX::XMConvertToRadians(0.0f));

	Shader::GetInstance()->RegisterLight(m_light.get());



}



/**
 * @brief �X�V����
 *
 * @param[in] elapsedTime     �t���[���Ԏ���
 * @param[in] currentPosition �e�̍��W
 * @param[in] currentAngle    �e�̊p�x
 *
 * @return �Ȃ�
 */
void Player::Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle)
{
	DirectX::Keyboard::KeyboardStateTracker* traker = Graphics::GetInstance()->GetKeyboardTracker();
	
	GetState()->Update(elapsedTime);
	m_sphere.SetCenter(currentPosition + GetPosition());
	m_light->Update(elapsedTime,currentPosition + GetPosition(), currentAngle * GetQuaternion());

	m_currentPosition = currentPosition + GetPosition();
	m_currentAngle = currentAngle * GetQuaternion();
	

	for (std::unique_ptr<GameObject>& part : m_bodyParts)
	{
		part->Update(elapsedTime,m_currentPosition,m_currentAngle);
	}

}




/**
 * @brief �`�揈��
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Player::Draw()
{
	GetState()->Render();


	auto debugFont = Graphics::GetInstance()->GetDebugFont();
	//Y��
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(m_currentAngle.y)), DirectX::SimpleMath::Vector2(50.0f, 50.0f));
	//���݂̗̑�
	debugFont->AddString(L"NowHP::", DirectX::SimpleMath::Vector2(0.0f, 100.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetCurrentHP())), DirectX::SimpleMath::Vector2(100.0f, 100.0f));
	//�U����
	debugFont->AddString(L"Attack::", DirectX::SimpleMath::Vector2(0.0f, 150.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetAttackPower())), DirectX::SimpleMath::Vector2(100.0f, 150.0f));
	//�h���
	debugFont->AddString(L"Diffence::", DirectX::SimpleMath::Vector2(0.0f, 200.0f));
	debugFont->AddString(TKTLib::StringToWchar(std::to_string(GetDiffence())), DirectX::SimpleMath::Vector2(100.0f, 200.0f));

	for (std::unique_ptr<GameObject>& part : m_bodyParts) 
	{
		part->Draw();
	}
}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Player::Finalize()
{
}


void Player::OnMessegeAccepted(Message::MessageID messageID)
{
	switch (messageID)
	{
	case Message::IDLING:
		GameObject::ChangeState(m_idlingState.get());
		break;
	case Message::MOVING:
		GameObject::ChangeState(m_movingState.get());
		break;
	case Message::ATTACK:
		GameObject::ChangeState(m_attackState.get());
		break;
	case Message::AVOIDANCE:
		break;
	case Message::DAMAGED:
		break;
	case Message::JUMPING:
		GameObject::ChangeState(m_jumpingState.get());
		break;
	default:
		break;
	}
}

void Player::CollisionResponce(GameObject* other)
{
	switch (other->GetObjectType())
	{
		case Tag::ObjectType::Enemy:
		{
			// �_���[�W���󂯂�
			
		}
		break;
		case Tag::ObjectType::Stage:
		{
			//�X�e�[�W�Ƃ̏Փˉ����@�����o��
			SetPosition(CollisionManager::GetInstance()->PushOut(dynamic_cast<Box*>(other->GetShape()), &m_sphere));
			//���x�����Z�b�g
			m_velocity.y = 0.0f;
			//�W�����v��ԂȂ�ҋ@��Ԃֈڍs
			if (GetState() == m_jumpingState.get()) 
			{
				OnMessegeAccepted(Message::IDLING);
			}

			break;
		}
	default:
		break;
	}
}


void Player::SetGem(Gem* gem, int index)
{
	m_pGem[index] = gem;
}

int Player::GetObjectNumber()
{
	return m_objectNumber;
}

DirectX::SimpleMath::Vector3 Player::GetVelocity()
{
	return m_velocity;
}

void Player::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}
