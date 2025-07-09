/**
 * @file   ModelParams.h
 *
 * @brief  ���f���`��ɕK�v�ȃp�����[�^�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t 2025 5/14
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================

// �N���X�̐錾 ===============================================================

namespace TKTLib
{


	// �N���X�̒�` ===============================================================
	/**
	  * @brief ModelParams
	  */
	class ModelParams
	{
		// �N���X�萔�̐錾 -------------------------------------------------
	public:


		// �f�[�^�����o�̐錾 -----------------------------------------------
	private:
		DirectX::Model* m_model;	///< ���f���f�[�^
		DirectX::SimpleMath::Vector3 m_position = { 0.0f,0.0f,0.0f };	///< ���f���̈ʒu
		DirectX::SimpleMath::Vector3 m_rotation = { 0.0f,0.0f,0.0f };	///< ���f���̉�]
		DirectX::SimpleMath::Vector3 m_scale = { 1.0f,1.0f,1.0f };	///< ���f���̊g�嗦

		// ���f���̃N�H�[�^�j�I����]
		DirectX::SimpleMath::Quaternion m_quaternion = { 0.0f,0.0f,0.0f,1.0f };
		// �����o�֐��̐錾 -------------------------------------------------
		// �R���X�g���N�^/�f�X�g���N�^
	public:
		// �R���X�g���N�^
		ModelParams();
		// �R�s�[�R���X�g���N�^
		ModelParams(ModelParams& modelParams);
		ModelParams(DirectX::Model* model, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);
		

		// �f�X�g���N�^
		~ModelParams();


		// ����
	public:
		// ���[���h�s����擾����
		DirectX::SimpleMath::Matrix GetWorldMatrix();

		//�@�擾�E�ݒ�
	public:
		// ���f���p�����[�^�̐ݒ�
		void SetModelParams(ModelParams& modelParams);
		// ���f���p�����[�^�E���f���̐ݒ�
		void SetModelParams(const DirectX::Model* model);
		// ���f���p�����[�^�̐ݒ�
		void SetModelParams(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& rotation, const DirectX::SimpleMath::Vector3& scale);
		// ���f���p�����[�^�E���W�̐ݒ�
		void SetModelParamsP(const DirectX::SimpleMath::Vector3& position);
		// ���f���p�����[�^�E��]�̐ݒ�
		void SetModelParamsR(const DirectX::SimpleMath::Vector3& rotation);
		// ���f���p�����[�^�E�g�嗦�̐ݒ�
		void SetModelParamsS(const DirectX::SimpleMath::Vector3& scale);

		// ���f���f�[�^�̎擾
		DirectX::Model* GetModel();
		// ���f���̈ʒu�̎擾
		DirectX::SimpleMath::Vector3 GetPosition() const;
		// ���f���̉�]�̎擾
		DirectX::SimpleMath::Vector3 GetRotation() const;
		// ���f���̊g�嗦�̎擾
		DirectX::SimpleMath::Vector3 GetScale() const;
		// ���f���̃N�H�[�^�j�I����]�̎擾
		DirectX::SimpleMath::Quaternion GetQuaternion() const;
		//�@��������
	private:

	};

}