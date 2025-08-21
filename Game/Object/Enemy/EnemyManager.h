/**
 * @file   EnemyManager.h
 *
 * @brief  �G�Ǘ��Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"../Enemy/Bat/Bat.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief EnemyManager
  */
class EnemyManager
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^

	//�G�z��
	std::list<std::unique_ptr<GameObject>> m_enemies;
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	EnemyManager();

	// �f�X�g���N�^
	~EnemyManager();


// ����
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();

	void Spawn();
//�@�擾�E�ݒ�
public:
	//�G���擾
	std::list<std::unique_ptr<GameObject>>& GetEnemies() { return m_enemies; }
//�@��������
private:

};

