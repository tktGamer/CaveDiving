/**
 * @file   Shape.h
 *
 * @brief  �����蔻��̊��N���X�Ɋւ���w�b�_�t�@�C��
 *
 * @author ����Җ� ���n�M��
 *
 * @date   ���t 2025/7/02
 */

 // ���d�C���N���[�h�̖h�~ =====================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ===================================================
#include "Game/Common/Collision/DisplayCollision.h"

// �N���X�̐錾 ===============================================================

// �N���X�̒�` ===============================================================
/**
  * @brief �����蔻��̊��N���X
  */
class Shape
{
// �N���X�萔�̐錾 -------------------------------------------------
public:
	//�`��̎��
	enum class ShapeType 
	{
		Box,        ///< �{�b�N�X
		Sphere,     ///< ��
		Capsule,    ///< �J�v�Z��
	};

// �f�[�^�����o�̐錾 -----------------------------------------------
private:
	ShapeType m_shapeType; ///< �`��̎��
// �����o�֐��̐錾 -------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
public:
	// �R���X�g���N�^
	Shape(ShapeType type);

	// �f�X�g���N�^
	~Shape();


// ����
public:
	virtual bool Intersects(Shape* other) = 0;

	virtual void AddDisplayCollision(Ito::DisplayCollision* dC)=0;
//�@�擾�E�ݒ�
public:
	ShapeType GetShapeType() const { return m_shapeType; }
//�@��������
private:

};

