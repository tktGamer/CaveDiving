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
#include "Game/Object/Character.h"
#include"Game/Common/Collision/Sphere.h"
#include "../Bat/Wing.h"
#include"Game/Object/Enemy/Bat/State/BatIdling.h"
#include"Game/Object/Enemy/Bat/State/BatAttack.h"
#include"Game/Object/Enemy/Bat/State/BatMoving.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief Bat
  */
class Bat :public Character
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

	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// ���b�Z�[�WID
	Message::MessageID m_messageID;

	//�����蔻��
	Sphere m_sphere;

	DirectX::SimpleMath::Vector3 m_velocity; // ���x 

	//�����Ă��邩
	bool m_isAlive;

	//���
	std::unique_ptr<IState> m_pCurrentState; // ���݂̏��
	std::unique_ptr<IState> m_idlingState; // �ҋ@��� 
	std::unique_ptr<IState> m_movingState; // �ړ����
	std::unique_ptr<IState> m_attackState; // �U�����

	//�H
	std::unique_ptr<Wing> m_rightWing; //�E��
	std::unique_ptr<Wing> m_leftWing;//����
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
	//�Փˉ�������
	void CollisionResponce(GameObject* other);

	//�@�擾�E�ݒ�
public:

	int GetObjectNumber() override;
	DirectX::SimpleMath::Vector3 GetVelocity();
	void SetVelocity(DirectX::SimpleMath::Vector3 v);
	//�����Ă��邩
	bool IsAlive() const;
	//�@��������
private:

};

