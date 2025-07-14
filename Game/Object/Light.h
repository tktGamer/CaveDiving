/**
 * @file   Light.h
 *
 * @brief  Light�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Object/GameObject.h"

// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Light
  */
class Light : public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct LightBuffer
	{
		DirectX::SimpleMath::Vector3 LightPosition;      // ���C�g�ʒu
		float LightInvSqrRadius; // ���C�g���͂������i2��̋t���j
		DirectX::SimpleMath::Vector3 LightColor;         // ���C�g�J���[
		float LightIntensity;    // ���C�g���x
		DirectX::SimpleMath::Vector4	Attenuation;

	};


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_lBuffer;
	LightBuffer m_lBuff;

	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^
	bool m_isOn; //���C�g�̃I���I�t���
	
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Light(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Light();


// ����
public:
	void Initialize();

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID);
//�@�擾�E�ݒ�
public:
	int GetObjectNumber() override;

	ID3D11Buffer* GetLightBuffer() const;

//�@��������
private:

};

