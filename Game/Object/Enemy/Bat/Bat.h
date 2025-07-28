/**
 * @file   Bat.h
 *
 * @brief  �R�E�����̓G�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include "Game/Object/GameObject.h"
#include"Game/Common/Collision/Sphere.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Bat
  */
class Bat :public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
	};


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^
	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;

	//�����蔻��
	Sphere m_sphere;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Bat(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Bat();


	void Initialize();

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID);

	//�@�擾�E�ݒ�
public:
	ID3D11InputLayout* GetInputLayout() const;
	ID3D11Buffer* GetCBuffer() const;

	int GetObjectNumber() override;
	//DirectX::SimpleMath::Vector3 GetVelocity();
	//void SetVelocity(DirectX::SimpleMath::Vector3 v);
	//�@��������
private:

};

