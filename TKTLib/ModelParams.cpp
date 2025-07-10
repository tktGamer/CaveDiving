/**
 * @file   ModelParams.cpp
 *
 * @brief  ���f���`��ɕK�v�ȃp�����[�^�Ɋւ���\�[�X�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "pch.h"
#include "ModelParams.h"
namespace TKTLib
{

	// �����o�֐��̒�` ===========================================================
	/**
	 * @brief �R���X�g���N�^
	 *
	 * @param[in] �Ȃ�
	 */
	ModelParams::ModelParams()
		: m_model{ nullptr }
		, m_position{ 0.0f,0.0f,0.0f }
		, m_rotation{ 0.0f,0.0f,0.0f }
		, m_scale{ 1.0f,1.0f,1.0f }
	{

	}
	/**
	 * @brief �R�s�[�R���X�g���N�^
	 *
	 * @param[in] modelParams �R�s�[���̃��f���p�����[�^
	 */
	ModelParams::ModelParams(ModelParams& modelParams)
		: m_model{ modelParams.m_model }
		, m_position{ modelParams.m_position }
		, m_rotation{ modelParams.m_rotation }
		, m_scale{ modelParams.m_scale }
	{
	}
	/**
	 * @brief �R���X�g���N�^
	 *
	 * @param[in] model ���f���f�[�^
	 * @param[in] position ���f���̈ʒu
	 * @param[in] rotation ���f���̉�]
	 * @param[in] scale ���f���̊g�嗦
	 */
	ModelParams::ModelParams(DirectX::Model* model, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale)
		: m_model{ model }
		, m_position{ position }
		, m_rotation{ rotation }
		, m_scale{ scale }
	{
	}



	/**
	 * @brief �f�X�g���N�^
	 */
	ModelParams::~ModelParams()
	{

	}

	/**
	 * @brief world�s����擾����
	 *
	 * @param[in] �Ȃ�
	 *
	 * @return world�s��
	 */
	DirectX::SimpleMath::Matrix ModelParams::GetWorldMatrix()
	{
		//���s�ړ��s����쐬����
		DirectX::SimpleMath::Matrix tras = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
		//Y���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotY = DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation.y);
		//X���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotX = DirectX::SimpleMath::Matrix::CreateRotationX(m_rotation.x);
		//Z���̉�]�s����쐬����
		DirectX::SimpleMath::Matrix rotZ = DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotation.z);
		//�g�嗦�s����쐬����
		DirectX::SimpleMath::Matrix scale = DirectX::SimpleMath::Matrix::CreateScale(m_scale);
		return scale * rotY * rotX * rotZ * tras;
	}

	/**
	 * @brief ���f���p�����[�^�̐ݒ�
	 *
	 * @param[in] modelParams ���f���p�����[�^
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParams(ModelParams& modelParams)
	{
		m_model = modelParams.m_model;
		m_position = modelParams.m_position;
		m_rotation = modelParams.m_rotation;
		m_scale = modelParams.m_scale;
	}



	/**
	 * @brief ���f���p�����[�^�E���f���̐ݒ�
	 *
	 * @param[in] model ���f���f�[�^
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParams(const DirectX::Model* model)
	{
		m_model = const_cast<DirectX::Model*>(model);
	}

	/**
	 * @brief ���f���p�����[�^�̐ݒ�
	 *
	 * @param[in] position ���f���̈ʒu
	 * @param[in] rotation ���f���̉�]
	 * @param[in] scale ���f���̊g�嗦
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParams(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& rotation, const DirectX::SimpleMath::Vector3& scale)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = scale;
	}

	/**
	 * @brief ���f���p�����[�^�E���W�̐ݒ�
	 *
	 * @param[in] position ���f���̈ʒu
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParamsP(const DirectX::SimpleMath::Vector3& position)
	{
		m_position = position;
	}

	/**
	 * @brief ���f���p�����[�^�E��]�̐ݒ�
	 *
	 * @param[in] rotation ���f���̉�]
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParamsR(const DirectX::SimpleMath::Vector3& rotation)
	{
		m_rotation = rotation;
	}

	/**
	 * @brief ���f���p�����[�^�E�g�嗦�̐ݒ�
	 *
	 * @param[in] scale ���f���̊g�嗦
	 *
	 * @return �Ȃ�
	 */
	void ModelParams::SetModelParamsS(const DirectX::SimpleMath::Vector3& scale)
	{
		m_scale = scale;
	}

	/**
	 * @brief ���f���f�[�^�̎擾
	 *
	 * @param[in] �Ȃ�
	 *
	 * @return ���f���f�[�^
	 */
	DirectX::Model* ModelParams::GetModel()
	{
		return m_model;
	}


	/**
	 * @brief ���f���̈ʒu���擾����
	 *
	 * @param[in] �Ȃ�
	 *
	 * @return ���f���̈ʒu
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetPosition() 
	{
		return m_position;
	}

	/**
	 * @brief ���f���̉�]���擾����
	 *
	 * @param[in] �Ȃ�
	 *
	 * @return ���f���̉�]
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetRotation() 
	{
		return m_rotation;
	}

	/**
	 * @brief ���f���̊g�嗦���擾����
	 *
	 * @param[in] �Ȃ�
	 *
	 * @return ���f���̊g�嗦
	 */
	DirectX::SimpleMath::Vector3& ModelParams::GetScale()
	{
		return m_scale;
	}
	DirectX::SimpleMath::Quaternion& ModelParams::GetQuaternion()
	{
		return m_quaternion;
	}
}