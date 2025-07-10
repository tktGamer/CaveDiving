/**
 * @file   CollisionManager.h
 *
 * @brief  CollisionManager�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ�
 *
 * @date   ���t
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include"Game/Common/Graphics.h"
#include"Game/Common/Collision/Box.h"
#include"Game/Common/Collision/Sphere.h"
// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief CollisionManager
  */
class CollisionManager
{
// �N���X�萔�̐錾 -------------------------------------------------
public:


// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	Graphics* m_graphics;	// �O���t�B�b�N�X�N���X�̃|�C���^
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	CollisionManager();

	// �f�X�g���N�^
	~CollisionManager();


// ����
public:
	void Initialize();

	void Update();

	void Draw();

	void Finalize();
	//�����o������
	DirectX::SimpleMath::Vector3 PushOut(Box* shape1, Sphere* shape2);
//�@�擾�E�ݒ�
public:

//�@��������
private:

};

