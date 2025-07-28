/**
 * @file   Hand.h
 *
 * @brief  ��Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Object/GameObject.h"
#include"Game/Object/Player/Pikel.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Hand
  */
class Hand : public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	DirectX::SimpleMath::Matrix m_world;

	std::unique_ptr<Pikel> m_pikel;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Hand(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Hand();


// ����
public:
	void Initialize() override;

	void Update(float elapsedTime, const DirectX::SimpleMath::Vector3& currentPosition, const DirectX::SimpleMath::Quaternion& currentAngle) override;


	void Draw() override;

	void Finalize();

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID);
	//�@�擾�E�ݒ�
public:
	int GetObjectNumber() override;

//�@��������
private:

};

