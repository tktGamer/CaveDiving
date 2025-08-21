/**
 * @file   Character.h
 *
 * @brief  �L�����̃X�e�[�^�X�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "../Object/GameObject.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief �L�����̃X�e�[�^�X
  */
class Character : public GameObject
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	//���݂̗̑�
	int m_currentHp;

	//�ő�̗�
	int m_hp;
	//�U����
	int m_attackPower;
	//�h���
	int m_diffence;

// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Character(int hp,int attack, int diffence,
		Tag::ObjectType type, GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);

	// �f�X�g���N�^
	~Character();


// ����
public:
	//�_���[�W
	void Damage(int damage);
//�@�擾�E�ݒ�
public:
	//���݂̗̑͂̎擾
	int& GetCurrentHP();
	// �̗͂̐ݒ�
	void SetMaxHP(int hp);
	// �̗͂̎擾
	int& GetMaxHP();
	// �U���͂̐ݒ�
	void SetAttackPower(int attack);
	// �U���͂̎擾
	int GetAttackPower();
	// �h��͂̐ݒ�
	void SetDiffence(int diffence);
	// �h��͂̎擾
	int GetDiffence();
//�@��������
private:

};

