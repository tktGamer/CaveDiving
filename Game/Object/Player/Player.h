/**
 * @file   Player.h
 *
 * @brief  ���L�����Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Object/GameObject.h"
#include "Game/Object/Gem/Gem.h"
#include "Game/Object/Light.h"
#include"Game/Object/Player/State/PlayerIdling.h"
#include"Game/Object/Player/State/PlayerMoving.h"
#include"Game/Common/Collision/Sphere.h"
// �N���X�̐錾 ===============================================================
class IState;
// �N���X�̒�` ===============================================================
/**
  * @brief Player
  */
class Player : public GameObject
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
	//	�֐�
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;

	Gem* m_pGem[3]; // �������Ă�����
	DirectX::SimpleMath::Vector3 m_velocity; // ���x 
	int m_hp; // HP
	std::unique_ptr<Light> m_light;

	//�����蔻��
	Sphere m_sphere;
	//���
	std::unique_ptr<IState> m_pCurrentState; // ���݂̏��
	std::unique_ptr<IState> m_idlingState; // �ҋ@��� 
	std::unique_ptr<IState> m_movingState; // �ړ����

	// �v���C���[�̑̂̃p�[�c
	std::vector<std::unique_ptr<GameObject>> m_bodyParts; 
	//�v���C���[�̌���
	DirectX::SimpleMath::Vector3 m_initialeDirection;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();


// ����
public:
	void Initialize();

	void Update(float elapsedTime) override;


	void Draw() override;

	void Finalize();

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID);

//�@�擾�E�ݒ�
public:
	ID3D11InputLayout* GetInputLayout() const;
	ID3D11Buffer* GetCBuffer() const;
	
	//��΂��Z�b�g
	void SetGem(Gem* gem,int index);
	int GetObjectNumber() override;
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);
//�@��������
private:

};

