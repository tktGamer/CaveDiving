/**
 * @file   AttackMotion.h
 *
 * @brief  �v���C���[�̍U���̃��[�V�����Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Object/Player/Hand.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief �v���C���[�̍U���̃��[�V����
  */
class AttackMotion
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	enum Attack
	{
		COMBO1,		// �R���{1
		COMBO2,		// �R���{2
		COMBO3,		// �R���{3
		JUMP,		// �W�����v�U��
	};


// �f�[�^�����o�̐錾 -----------------------------------------------
private:

	Hand* m_pRightHand;  //�E��̃|�C���^
	Hand* m_pLeftHand;  //����̃|�C���^

	float m_motionLerp;//���[�V�����̕�Ԓl

	Attack m_attackType;
	bool m_isNextAttack; //���̍U�������邩�ǂ���
	std::function<bool()> m_attackFunc;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	AttackMotion(Hand* pRightHand, Hand* LeftHand);

	// �f�X�g���N�^
	~AttackMotion();


// ����
public:
	void Initialize();

	bool Update();


	void Reset();

	bool FirstAttack();
	bool SecondAttack();
	bool ThirdAttack();
//�@�擾�E�ݒ�
public:
	void SetIsNextAttack(bool isNext);
//�@��������
private:

};

