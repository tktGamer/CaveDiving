// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "Camera.h"

using namespace DirectX;

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in] �Ȃ�
 */
Camera::Camera()
    :m_up{0.0f,1.0f,0.0f}
    ,m_view{}
	, m_eyePos{}
	, m_targetPos{}
	, m_distance{ 0.0f, 0.0f, 10.0f } // �f�t�H���g�̋�����ݒ�
{
}

Camera::~Camera()
{
}


/**
 * @brief ����������
 *
 * @param[in] position �J�����̈ʒu
 *
 * @return �Ȃ�
 */
void Camera::Initialize(DirectX::SimpleMath::Vector3 eyePos)
{
	m_eyePos = eyePos;
    m_up={ 0.0f,1.0f,0.0f };

}

/**
 * @brief �X�V����
 *
 * @param[in] 
 *
 * @return �Ȃ�
 */
void Camera::Update(float elapsedTime)
{
    DirectX::SimpleMath::Vector3 pos = m_target + m_distance; // �{�����B���Ă���ׂ��J�����ʒu
    m_eyePos = DirectX::SimpleMath::Vector3::Lerp(m_eyePos, pos, elapsedTime * 3.0f); // Lerp����
    //�����ō쐬�����r���[�s��Őݒ肷��
    m_view = SimpleMath::Matrix::CreateLookAt(
        m_eyePos,       //�J�����̈ʒu
        m_target,    //�^�[�Q�b�g�̈ʒu
        m_up);          //�J�����̏�x�N�g��



}

/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void Camera::Finalize()
{
}


void Camera::SetEyePos(DirectX::SimpleMath::Vector3 position)
{
	m_eyePos = position;
}

void Camera::SetEyePosX(float posX)
{
	m_eyePos.x = posX;
}

void Camera::SetEyePosY(float posY)
{
	m_eyePos.y = posY;
}

void Camera::SetEyePosZ(float posZ)
{
	m_eyePos.z = posZ;
}

void Camera::SetTartet(const DirectX::SimpleMath::Vector3& targetPos, const DirectX::SimpleMath::Quaternion& rotate)
{
	m_targetPos = &targetPos;
	m_targetRotate = &rotate; // �^�[�Q�b�g�̉�]���ݒ�
}


void Camera::SetDistance(DirectX::SimpleMath::Vector3 distance)
{
	m_distance = distance;
}

DirectX::SimpleMath::Matrix Camera::GetView()
{
    return m_view;
}
