/**
 * @file   GameObject.cpp
 *
 * @brief  �w�w�w�w�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "GameObject.h"


// �I�u�W�F�N�g�ԍ�
int GameObject::s_objectNumber = -1;

// �I�u�W�F�N�g���J�E���g�A�b�v����
int GameObject::CountUpNumber() { return s_objectNumber++; }

// �����o�֐��̒�` ===========================================================
/**
 * @brief �R���X�g���N�^
 *
 * @param[in]  objectType �I�u�W�F�N�g�̎��
 * @param[in]  modelParams ���f���p�����[�^
 * 
 */
GameObject::GameObject(ObjectType objectType, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	: m_objectType{ objectType }
	, m_graphics{ Graphics::GetInstance() }
	, m_texture{}
	, m_model{ nullptr }
	, m_pCurrentState{ nullptr }
	, m_currentMessage{}
	, m_position{initialPosition} // �����ʒu��ݒ�
	, m_quaternion{ DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, initialAngle) } // �����N�H�[�^�j�I����ݒ�
	, m_scale{ 1.0f, 1.0f, 1.0f } // �����g�嗦��ݒ�
	, m_parent{ parent }
	, m_currentPosition{}
	, m_currentAngle{}
{
}

/**
 * @brief �f�X�g���N�^
 */
GameObject::~GameObject()
{

}



/**
 * @brief ����������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameObject::Initialize()
{

}



/**
 * @brief �I������
 *
 * @param[in] �Ȃ�
 *
 * @return �Ȃ�
 */
void GameObject::Finalize()
{

}



/**
 * @brief �e�N�X�`����ݒ肷��
 *
 * @param[in] tex �e�N�X�`��
 *
 * @return �Ȃ�
 */
void GameObject::SetTexture(ID3D11ShaderResourceView** tex)
{
	m_texture = tex;
}

/**
 * @brief �e�N�X�`�����擾����
 *
 * @param[in] �Ȃ�
 *
 * @return �e�N�X�`��
 */
ID3D11ShaderResourceView** GameObject::GetTexture()
{
	return m_texture;
}


/**
 * @brief �I�u�W�F�N�g�̎�ނ��擾����
 *
 * @param[in] �Ȃ�
 *
 * @return �I�u�W�F�N�g�̎��
 */
GameObject::ObjectType GameObject::GetObjectType() const
{
	return m_objectType;
}

/**
 * @brief �O���t�B�b�N�X�N���X�̃|�C���^���擾����
 *
 * @param[in] �Ȃ�
 *
 * @return �O���t�B�b�N�X�N���X�̃|�C���^
 */
Graphics* GameObject::GetGraphics() const
{
	return m_graphics;
}
