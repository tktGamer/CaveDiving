/**
 * @file   Pikel.h
 *
 * @brief  ��͂��i�v���C���[�̕���j�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Object/GameObject.h"
#include"Game/Common/Collision/DisplayCollision.h"
#include"Game/Common/Collision/Sphere.h"

// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Pikel
  */
class Pikel : public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	DirectX::SimpleMath::Matrix m_world;

	Ito::DisplayCollision m_display;
	//�����蔻��
	Sphere m_sphere;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Pikel(GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Pikel();


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

//�@��������
private:

};

